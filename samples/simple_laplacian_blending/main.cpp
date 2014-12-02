/*

PICCANTE
The hottest HDR imaging library!
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

PICCANTE is free software; you can redistribute it and/or modify
under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 3.0 of
the License, or (at your option) any later version.

PICCANTE is distributed in the hope that it will be useful, but
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License
( http://www.gnu.org/licenses/lgpl-3.0.html ) for more details.

*/

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{

    printf("Reading images...");

    pic::Image imgA, imgB, maskA;
    imgA.Read("../data/input/laplacian/image.png", pic::LT_NOR);
    imgB.Read("../data/input/laplacian/target.png", pic::LT_NOR);
    maskA.Read("../data/input/laplacian/mask.png", pic::LT_NOR);

    printf("Ok\n");

    printf("Are images valid? ");
    if( imgA.isValid() && imgB.isValid() && maskA.isValid()) {
        printf("OK\n");

        pic::Image maskB(maskA.width, maskA.height, maskA.channels);
        maskB.Assign(1.0f);
        maskB.Sub(&maskA);

        //Creating Laplacian pyramids
        pic::Pyramid pyrA(&imgA, true, 4);
        pic::Pyramid pyrB(&imgB, true, 4);

        //Creating Gaussian pyramids
        pic::Pyramid pyrMA(&maskA, false, 4);
        pic::Pyramid pyrMB(&maskB, false, 4);

        //Blending
        pyrA.Mul(&pyrMA);
        pyrB.Mul(&pyrMB);

        pyrA.Add(&pyrB);

        pic::Image *imgOut = pyrA.Reconstruct();

        imgOut->Write("../data/output/laplacian_blending_result.png", pic::LT_NOR);

    } else {
        printf("All images are not valid!\n");
    }

    return 0;
}