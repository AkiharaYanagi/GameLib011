//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "testEnumFile.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Test::Test ()
	{
	}

	Test::~Test ()
	{
	}

	void Test::Load ()
	{
		//サブディレクトリ ファイル列挙
		TRACE_F ( _T ( "\n//------------------------------------\n" ) );
		TRACE_F ( _T ( "ファイル列挙開始\n" ) );
		Find ( _T ( "archive" ) );

		//結果表示
		TRACE_F ( _T ( "\n//------------------------------------\n" ) );
		TRACE_F ( _T ( "検索結果\n" ) );
		for ( tstring filename : m_vFilename )
		{
			TRACE_F ( filename.c_str () );
			TRACE_F ( _T ( "\n" ) );
		}
		TRACE_F ( _T ( "\n" ) );

		TASK_VEC::Load ();
	}

	void Test::Find ( LPCTSTR path )
	{
		WIN32_FIND_DATA findData;
		TCHAR dir [ MAX_PATH ] = _T ( "" );
		_stprintf_s ( dir, MAX_PATH, _T("%s/*.*"), path );

		HANDLE hFind = ::FindFirstFile ( dir, & findData );
		TRACE_F ( _T ( "%s\n" ), dir );

		do
		{
			//システムファイル(Thumbs.dbなど)はとばす
			if ( findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) { continue; }

			//ディレクトリの場合再帰
			if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				if ( _tcscmp ( _T("."), findData.cFileName ) == 0 ) { continue; }
				if ( _tcscmp ( _T(".."), findData.cFileName ) == 0 ) { continue; }
				if ( _tcscmp ( path, findData.cFileName ) == 0 ) { continue; }

				TCHAR subpath [ MAX_PATH ] = _T ( "" );
				_stprintf_s ( subpath, MAX_PATH, _T ( "%s/%s" ), path, findData.cFileName);
				Find ( subpath );
			}
			//ファイルの場合
			else
			{
				tstring fn ( findData.cFileName );
				m_vFilename.push_back ( fn );
				TRACE_F ( findData.cFileName );
				TRACE_F ( _T ( "\n" ) );
			}
		} while ( ::FindNextFile ( hFind, & findData ) );

		FindClose ( hFind );
	}


}	//namespace GAME

