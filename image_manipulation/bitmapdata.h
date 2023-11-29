

#include "fileio.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef RGB2GRAY_BITMAPDATA_H
#define RGB2GRAY_BITMAPDATA_H

namespace creatingly{

    class bitmapdata{

    public:

        struct Pixel{

        public:

            unsigned char Red=0;

            unsigned char Green=0;

            unsigned char Blue=0;

            unsigned char Alpha=0;

            int ToInt(){
                return (unsigned char) (Red) << 24 |
                       (unsigned char) (Green) << 16 |
                       (unsigned char) (Blue) << 8 |
                       (unsigned char) (Alpha);
            }

            void FromInt(int color){

                char arr[4];

                memcpy(arr, &color, sizeof(int));

                Red=arr[0];

                Green=arr[1];

                Blue=arr[2];

                Alpha=arr[3];

                free(arr);
            }

            void FromArray(char * arr,int length){
                if(length>=1){
                    Red=arr[0];
                }
                if(length>=2){
                    Green=arr[1];
                }
                if(length>=3){
                    Blue=arr[2];
                }
                if(length>=4){
                    Alpha=arr[3];
                }
            }
        };

    private:

        enum Format:short {
            ///
            /// Windows 3.1x, 95, NT, ... etc.
            ///
            BM=0x424D,

            ///
            /// OS/2 struct bitmap array
            ///
            BA=0x4241,

            ///
            /// OS/2 struct color icon
            ///
            CI=0x4349,

            ///
            /// OS/2 const color pointer
            ///
            CP=0x4350,

            ///
            /// OS/2 struct icon
            ///
            IC=0x4943,

            ///
            /// OS/2 pointer
            ///
            PT=0x5054,
        };

        enum Version:int{
            ///
            /// Windows 2.0 or later, OS/2 1.x
            ///
            BITMAPCOREHEADER=0x0000000C,

            ///
            /// OS/2 BITMAPCOREHEADER2
            /// Adds halftoning. Adds RLE and Huffman 1D compression.
            ///
            OS22XBITMAPHEADER16=0x00000010,

            ///
            /// This variant of the previous header contains only the first 16 bytes and the remaining bytes are assumed to be zero values.
            /// An example of such a case is the graphic pal8os2v2-16.bmp[10] of the BMP Suite.
            ///
            OS22XBITMAPHEADER64=0x00000040,

            ///
            /// Windows NT, 3.1x or later
            /// Extends bitmap width and height to 4 bytes. Adds 16 bpp and 32 bpp formats. Adds RLE compression.
            ///
            BITMAPINFOHEADER=0x00000028,

            ///
            /// Undocumented
            /// Adds RGB bit masks.
            ///
            BITMAPV2INFOHEADER=0x00000034,

            ///
            /// Not officially documented, but this documentation was posted on Adobe's forums
            /// by an employee of Adobe with a statement that the standard was at one point in the past included in official MS documentation
            /// Adds alpha channel bit mask.
            ///
            BITMAPV3INFOHEADER=0x00000038,

            ///
            /// Windows 2.0 or later, OS/2 1.x
            /// Windows NT 4.0, 95 or later
            ///
            BITMAPV4HEADER=0x0000006C,

            ///
            /// Windows 2.0 or later, OS/2 1.x
            /// Windows NT 5.0, 98 or later
            ///
            BITMAPV5HEADER=0x0000007C
        };

        enum CompressionMethod:int{
            ///
            /// none
            /// Most common
            ///
            BI_RGB=0x00000000,

            ///
            /// RLE 8-bit/pixel
            /// Can be used only with 8-bit/pixel bitmaps
            ///
            BI_RLE8=0x00000001,

            ///
            /// RLE 4-bit/pixel
            /// Can be used only with 4-bit/pixel bitmaps
            ///
            BI_RLE4=0x00000002,

            ///
            /// 	OS22XBITMAPHEADER: Huffman 1D
            /// BITMAPV2INFOHEADER: RGB bit field masks, BITMAPV3INFOHEADER+: RGBA
            ///
            BI_BITFIELDS=0x00000003,

            ///
            /// OS22XBITMAPHEADER: RLE-24
            /// BITMAPV4INFOHEADER+: JPEG image for printing
            ///
            BI_JPEG=0x00000004,

            ///
            /// BITMAPV4INFOHEADER+: PNG image for printing
            ///
            BI_PNG=0x00000005,

            ///
            /// RGBA bit field masks
            /// only Windows CE 5.0 with .NET 4.0 or later
            ///
            BI_ALPHABITFIELDS=0x00000006,

            ///
            /// none
            /// only Windows Metafile CMYK[4]
            ///
            BI_CMYK=0x0000000B,

            ///
            /// RLE-8
            /// only Windows Metafile CMYK
            ///
            BI_CMYKRLE8=0x0000000C,

            ///
            /// 	RLE-4
            /// only Windows Metafile CMYK
            ///
            BI_CMYKRLE4=0x0000000D,
        };

        enum ColorSpaceType:int{
            LCS_CALIBRATED_RGB=0x00000000,
            LCS_sRGB=0x73524742,
            LCS_WINDOWS_COLOR_SPACE=0x57696e20,
            PROFILE_LINKED=0x4c494e4b,
            PROFILE_EMBEDDED=0x4d424544,
            LCS_GM_BUSINESS=0x00000001,
            LCS_GM_GRAPHICS=0x00000002,
            LCS_GM_IMAGES=0x00000003,
            LCS_GM_ABS_COLORIMETRIC=0x00000004
        };

        struct ColorSpaceRed{
        public:
            int x;
            int y;
            int z;
        };

        struct ColorSpaceGreen{
        public:
            int x;
            int y;
            int z;
        };

        struct ColorSpaceBlue{
        public:
            int x;
            int y;
            int z;
        };

        struct Header{
        public:
            ///
            /// The header field used to identify the BMP and DIB file is 0x42 0x4D in hexadecimal, same as BM in ASCII
            ///
            Format format;

            ///
            /// The size of the BMP file in bytes
            ///
            int    filesize;

            ///
            /// Reserved; actual value depends on the application that creates the image, if created manually can be 0
            ///
            short  reserved1;

            ///
            /// Reserved; actual value depends on the application that creates the image, if created manually can be 0
            ///
            short  reserved2;

            ///
            /// The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found.
            ///
            int    offset;
        };

        struct DIBHeader{

        public:
            ///
            /// Number of bytes in the DIB header
            ///
            Version version;

            ///
            /// Width of the bitmap in pixels
            ///
            short   width;

            ///
            /// Height of the bitmap in pixels. Positive for bottom to top pixel order.
            ///
            short   height;

            ///
            /// Number of color planes being used
            ///
            short   colorPlanes;

            ///
            /// Number of bits per pixel
            ///
            short   bitsPerPixel;

            ///
            /// Compression method
            ///
            CompressionMethod compressionMethod;

            ///
            /// Size of the raw bitmap data (including padding)
            ///
            int SRBD;

            ///
            /// Print resolution of the image horizontal, 72 DPI × 39.3701 inches per metre yields 2834.6472
            ///
            int PRIH;

            ///
            /// Print resolution of the image vertical, 72 DPI × 39.3701 inches per metre yields 2834.6472
            ///
            int PRIV;

            ///
            /// Number of colors in the palette
            ///
            int NOP;

            ///
            /// Important colors
            ///
            int IC;

            int redMask;

            int greenMask;

            int blueMask;

            int alphaMask;

            ColorSpaceType colorSpaceType;

            ColorSpaceRed colorSpaceRed;

            ColorSpaceGreen colorSpaceGreen;

            ColorSpaceBlue colorSpaceBlue;

            int gammaRed;

            int gammaGreen;

            int gammaBlue;

            int intent;

            int profileData;

            int profileSize;

            int reservedV5;

        };

        struct ExtraBitMasks{

        };

        struct ColorTable{

        };

        struct Gap1{

        };

        struct Gap2{

        };

        struct ICC{

        };

        void LoadHeaderData(const fileio *_bmpfile);

        void LoadDIBHeader(const fileio *_bmpfile);

    public:

        bitmapdata() {};

        ///
        /// not optional
        /// 14 bytes
        /// To store general information about the bitmap image file
        ///
        Header header;

        ///
        /// not optional
        /// Fixed size
        /// To store detailed information about the bitmap image and define the pixel format
        ///
        DIBHeader    dib;

        ///
        /// optional
        /// 12 to 16 bytes
        /// To define the pixel format
        /// Present only in case the DIB header is the BITMAPINFOHEADER and the Compression Method member is set to either BI_BITFIELDS or BI_ALPHABITFIELDS
        ///
        ExtraBitMasks extraBitMasks;

        ///
        /// semi optional
        /// Variable size
        /// To define colors used by the bitmap image data (Pixel array)
        /// Mandatory for color depths ≤ 8 bits
        ///
        ColorTable colorTable;

        ///
        /// optional
        /// Variable size
        /// Structure alignment
        /// An artifact of the File offset to Pixel array in the Bitmap file header
        ///
        Gap1 gap1; // optional, Variable size, Structure alignment

        ///
        /// optional
        /// Variable size
        /// Structure alignmenat
        /// An artifact of the ICC profile data offset field in the DIB header
        ///
        Gap2 gap2; // optional, Variable size, Structure alignment

        ///
        /// optional
        /// Variable size
        /// To define the color profile for color management
        /// Can also contain a path to an external file containing the color profile. When loaded in memory as "non-packed DIB", it is located between the color table and Gap1.
        ///
        ICC icc;

        bitmapdata(const fileio *_bmpfile);
    };
}

#endif //RGB2GRAY_BITMAPDATA_H
