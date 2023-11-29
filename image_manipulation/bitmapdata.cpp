


#include "bitmapdata.h"

namespace creatingly {

    void bitmapdata::LoadHeaderData(const fileio *_bmpfile){
        header.format=(Format)(_bmpfile->GetWordAt(0));
        header.filesize=_bmpfile->GetDWordAt(2, true);
        header.reserved1=_bmpfile->GetWordAt(6);
        header.reserved2=_bmpfile->GetWordAt(8);
        header.offset=_bmpfile->GetDWordAt(10,true);
    }

    void bitmapdata::LoadDIBHeader(const fileio *_bmpfile){
        dib.version=(Version)(_bmpfile->GetDWordAt(14, true));
        dib.width=_bmpfile->GetDWordAt(18,true);
        dib.height=_bmpfile->GetDWordAt(22,true);
        dib.colorPlanes=_bmpfile->GetWordAt(26,true);
        dib.bitsPerPixel=_bmpfile->GetWordAt(28,true);

        if(dib.version>=Version::BITMAPINFOHEADER){
            dib.compressionMethod=(CompressionMethod)(_bmpfile->GetDWordAt(30,true));
            dib.SRBD=_bmpfile->GetDWordAt(34, true);
            dib.PRIH=_bmpfile->GetDWordAt(38, true);
            dib.PRIV=_bmpfile->GetDWordAt(42, true);
            dib.NOP=_bmpfile->GetDWordAt(46, true);
            dib.IC=_bmpfile->GetDWordAt(50, true);
        }

        if(dib.version>=Version::BITMAPV2INFOHEADER){
            dib.redMask=_bmpfile->GetDWordAt(54, true);
            dib.greenMask=_bmpfile->GetDWordAt(58, true);
            dib.blueMask=_bmpfile->GetDWordAt(62, true);
        }

        if(dib.version>=Version::BITMAPV3INFOHEADER){
            dib.alphaMask=_bmpfile->GetDWordAt(66, true);
        }

        if(dib.version>=Version::BITMAPV4HEADER){
            dib.colorSpaceType=(ColorSpaceType)(_bmpfile->GetDWordAt(70, true));
            dib.colorSpaceRed.x=_bmpfile->GetDWordAt(74, true);
            dib.colorSpaceRed.y=_bmpfile->GetDWordAt(78, true);
            dib.colorSpaceRed.z=_bmpfile->GetDWordAt(82, true);
            dib.colorSpaceGreen.x=_bmpfile->GetDWordAt(86, true);
            dib.colorSpaceGreen.y=_bmpfile->GetDWordAt(90, true);
            dib.colorSpaceGreen.z=_bmpfile->GetDWordAt(94, true);
            dib.colorSpaceBlue.x=_bmpfile->GetDWordAt(98, true);
            dib.colorSpaceBlue.y=_bmpfile->GetDWordAt(102, true);
            dib.colorSpaceBlue.z=_bmpfile->GetDWordAt(106, true);
            dib.gammaRed=_bmpfile->GetDWordAt(110, true);
            dib.gammaGreen=_bmpfile->GetDWordAt(114, true);
            dib.gammaBlue=_bmpfile->GetDWordAt(118, true);
        }

        if(dib.version>=Version::BITMAPV5HEADER){
            dib.intent=_bmpfile->GetDWordAt(122, true);
            dib.profileData=_bmpfile->GetDWordAt(126, true);
            dib.profileSize=_bmpfile->GetDWordAt(130, true);
            dib.reservedV5=_bmpfile->GetDWordAt(134, true);
        }
    }

    bitmapdata::bitmapdata(const fileio *_bmpfile){
        LoadHeaderData(_bmpfile);
        LoadDIBHeader(_bmpfile);
    }

}
