/***********************************************************************

 Copyright (C) 2011 by Zach Gage

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 ************************************************************************/

#include "LinearTexture.h"

void LinearTexture::loadTexture(string textureName, int glType)
{
	ofImage loader;
	loader.setUseTexture(false);
	loader.loadImage(textureName);
	allocate(loader.getWidth(), loader.getHeight(), glType);
	loadData(loader.getPixels(), loader.getWidth(), loader.getHeight(), glType);

	loader.clear();
}
void LinearTexture::loadTextureFromPVR(string textureName, int glType)
{

}
