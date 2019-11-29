//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "qrcode\qrencode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
void createQrCode(TImage *image, String data);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        String uri = "http://www.makinnet";

        createQrCode(Form1->Image1, uri);


}

void createQrCode(TImage *image, String data){

        QRcode *code = QRcode_encodeString(data.c_str(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);

        int width = code->width;
        int rate = 0;
        int minSize = 0;

        if(image->Width > image->Height){
            minSize = image->Height;
        }else{
            minSize = image->Width;
        }

        rate = minSize / width;

        int paddingX=(image->Width - width * rate)/2;
        int paddingY=(image->Height - width * rate)/2;

        for(int x=0;x<width;x++){
           for(int y=0;y<width;y++){
               int x1 = y * rate;
               int y1 = x * rate;

               for(int tx1=0;tx1<rate;tx1++){
                   for(int ty1=0;ty1<rate;ty1++){
                      if(code->data[y+x*width]&1){
                          image->Canvas->Pixels[x1+tx1+paddingX][y1+ty1+paddingY]=clBlack;
                      }else{
                          image->Canvas->Pixels[x1+tx1+paddingX][y1+ty1+paddingY]=clWhite;
                      }
                   }
               }
           }
        }

        image->Refresh();
}


//---------------------------------------------------------------------------

 