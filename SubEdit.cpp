//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("SubEdit.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", FormPytanie);
USEFORM("Unit3.cpp", FormInformacje);
USEFORM("UnitPomoc.cpp", FormPomoc);
USEFORM("UnitNapis1.cpp", FormNapisy);
USEFORM("Unit4.cpp", FormUstawienia);
USEFORM("UnitMozliwosci.cpp", FormMozliwosci);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Subtitle Editor  2000 by sir Arthur";
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TFormPytanie), &FormPytanie);
                 Application->CreateForm(__classid(TFormInformacje), &FormInformacje);
                 Application->CreateForm(__classid(TFormPomoc), &FormPomoc);
                 Application->CreateForm(__classid(TFormNapisy), &FormNapisy);
                 Application->CreateForm(__classid(TFormUstawienia), &FormUstawienia);
                 Application->CreateForm(__classid(TFormMozliwosci), &FormMozliwosci);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
