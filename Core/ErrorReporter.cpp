#include "StdAfx.h"
#include "ErrorReporter.h"

std::string ErrorReporter::PublicStorage;

void ErrorReporter::Report()
{
    std::string text;
#pragma region text �ʱ�ȭ
    char itoaBuffer[12];
    if ( filename ) {
        text += filename;
        if ( 0xffffffff != linenum ) {
            text += '(';
            _itoa_s( linenum, itoaBuffer, 10 );
            text += itoaBuffer;
            text += ')';
        }
        text += '\n';
    }
    if ( function ) {
        text += "�Լ� �̸� : ";
        text += function;
        text += '\n';
    }
    if ( command ) {
        text += "���� ���� : ";
        text += command;
        text += '\n';
    }
    if ( 0xffffffff != hr ) {
        text += "HRESULT �ڵ� : 0x";
        _itoa_s( hr, itoaBuffer, 16 );
        text += itoaBuffer;
        text += '\n';
    }
    if ( message ) {
        text += message;
        if ( text.back() != '\n' ) text += '\n';
    }
#pragma endregion

#pragma region ���� ǥ��
	if ( IsDebuggerPresent() ) {
		OutputDebugStringA ( "======================================"
            "========================================\n" );
        OutputDebugStringA( text.c_str() );
		OutputDebugStringA ( "------------------------------------------------------------------------------\n" );
        DebugBreak();
    } else {
		AllocConsole();
		AttachConsole( GetCurrentProcessId() );
		FILE* dummy;
		freopen_s(&dummy, "CON", "w", stdout);
        printf( "%s\n", text.c_str() );
		system("pause");
		FreeConsole();
	}
#pragma endregion

}
