//=================================================================================================
//
// ゲームテキストファイル実装
//
//=================================================================================================


//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameTextFile.h"


namespace GAME
{


	TextFile::TextFile () : m_strArray ( nullptr )
	{
		setlocale ( LC_ALL, "japanese" );
		std::locale::global ( std::locale("japanese") );
		m_nLine = 0;
		m_index = 0;
	}

	TextFile::~TextFile ()
	{
		if ( m_strArray ) { delete[] m_strArray; }
		m_strArray = nullptr;
		m_ifstrm.close ();
	}

	void TextFile::Load ()
	{
		//ファイルストリーム初期化
		std::string str;
		m_ifstrm.open ( TEXT("textdata.txt") );
		if ( ! m_ifstrm )
		{
			////TRACE_F ( TEXT("file open error.\n") );
			return;
		}

		//行数数え上げ
		size_t maxLine = 0;		//最大文字数
		while ( ! m_ifstrm.fail () )
		{
			getline ( m_ifstrm, str );
			if ( maxLine < str.size () ) maxLine = str.size ();	//最大文字数の更新
			if ( m_ifstrm.eof () ) break;
			m_nLine++;
		}

		//テキスト配列の確保
		m_strArray = new tstring [m_nLine];		//解放はデストラクタで行う

		//ファイルの先頭に戻る
		m_ifstrm.clear ();
		m_ifstrm.seekg ( 0, std::ios::beg );

		//読込
		LPTSTR ptstr = new TCHAR[maxLine];
		size_t n = 0;
		for ( UINT i = 0; i < m_nLine; i++ )
		{
			getline ( m_ifstrm, str );
			mbstowcs_s ( &n, ptstr, maxLine, str.c_str(), _TRUNCATE );
			m_strArray[i].assign ( ptstr );
		}
		delete[] ptstr;
	}



}	//namespace GAME

