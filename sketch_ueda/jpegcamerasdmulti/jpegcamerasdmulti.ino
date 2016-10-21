#include <SoftwareSerial.h>
#include <SD.h>
#include "JPEGCamera.h"

#define CABLESELECTPIN	(10)
// ファイル名は、8.3形式対応（拡張子でない部分は8文字以内にしないと、SD.open()に失敗する）
#define STRING_FILENAMEFORMAT		("test%04d.jpg")

JPEGCamera camera;

void setup()
{
	Serial.begin(9600);
	Serial.println( "start." );
	
	// カメラ関数のレスポンス用変数
	char szResponse[32];

	// カメラの開始
	camera.begin();
	
	// EhternetShieldの場合は、CSはpin4だが、
	// その場合でも、pin10は、出力ピンに設定する必要がある。
	pinMode(10, OUTPUT);	
	// SDカードの開始
	if( !SD.begin(CABLESELECTPIN) )
	{
		Serial.println( "Failed : SD.begin() ");
		return;
	}

	// カメラのリセット
	camera.reset( szResponse );
	delay(3000);
}

void TakeAndSavePicture( int& riFileIndex )
{
	// カメラ関数のレスポンス用変数
	char szResponse[32];

	// ファイル名
	char szFileName[16];

	Serial.println( "Start : TakeAndSavePicture" );

	while( 1 )
	{
		sprintf( szFileName, STRING_FILENAMEFORMAT, riFileIndex );
		if( false == SD.exists(szFileName) )
		{
			break;
		}
		riFileIndex++;
	}

	File file = SD.open( szFileName, FILE_WRITE );
	if( false == file )
	{
		Serial.println( "Failed : SD.open()" );
		return;
	}
	Serial.print( "FileNamet : " );
	Serial.println( szFileName );

	// 写真撮影
	camera.takePicture( szResponse );

	// 画像サイズの取得
	int iPictureSize;
	camera.getSize(szResponse, &iPictureSize);
	Serial.print( "PictureSize : " );
	Serial.println( iPictureSize );

	// JPEG画像の取り出し
	// JPEG画像は、「FFD8」から「FFD9」までを切り出すことで作成する。
	int iIndex = 0;
	boolean bFoundStart = false;
	boolean bFoundEnd = false;
	while( iIndex < iPictureSize )
	{
		// データ取り出し
		int iCountReadData = camera.readData( szResponse, iIndex );
		int iStart = 0;
		int iEnd = iCountReadData;
		for( int i = 0; i < iCountReadData; i += 2 )
		{
			if( (char)0xFF == szResponse[i]
			 && (char)0xD8 == szResponse[i+1] )
			{
				iStart = i;
				bFoundStart = true;
			}
			if( (char)0xFF == szResponse[i]
			 && (char)0xD9 == szResponse[i+1] )
			{
				iEnd = i + 2;
				bFoundEnd = true;
			}
		}
		
		if( bFoundStart )
		{
			file.write( (uint8_t*)&szResponse[iStart], iEnd - iStart );
			if( bFoundEnd )
			{
				bFoundStart = false;
				bFoundEnd = false;
			}
		}
		
		iIndex += iCountReadData;
	}

	file.close();

	// カメラのストップ
	camera.stopPictures( szResponse );

	Serial.println( "End : TakeAndSavePicture" );
	Serial.println( millis() );
}

void loop()
{
	static int iFileIndex = 1;
	
	TakeAndSavePicture( iFileIndex );
	iFileIndex++;
}
