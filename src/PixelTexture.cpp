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

#include "PixelTexture.h"

void PixelTexture::loadTexture(string textureName, int glType)
{
	ofImage loader;
	loader.setUseTexture(false);
	loader.loadImage(textureName);
	allocate(loader.getWidth(), loader.getHeight(), glType);
	loadData(loader.getPixels(), loader.getWidth(), loader.getHeight(), glType);
	
	loader.clear();
}

void PixelTexture::allocate(int w, int h, int internalGlDataType){
	allocate(w, h, internalGlDataType, ofGetUsingArbTex());
}

void PixelTexture::allocate(int w, int h, int internalGlDataType, bool bUseARBExtention){
	
	//our graphics card might not support arb so we have to see if it is supported.
#ifndef TARGET_OPENGLES
	if (bUseARBExtention && GL_ARB_texture_rectangle){
		texData.tex_w = w;
		texData.tex_h = h;
		texData.tex_t = w;
		texData.tex_u = h;
		texData.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
	} else 
#endif
	{
		//otherwise we need to calculate the next power of 2 for the requested dimensions
		//ie (320x240) becomes (512x256)
		texData.tex_w = ofNextPow2(w);
		texData.tex_h = ofNextPow2(h);
		texData.tex_t = 1.0f;
		texData.tex_u = 1.0f;
		texData.textureTarget = GL_TEXTURE_2D;
	}
	
	texData.glTypeInternal = internalGlDataType;
	
	
	// MEMO: todo, add more types
	
	// attempt to free the previous bound texture, if we can:
	clear();
	
	glGenTextures(1, (GLuint *)&texData.textureID);   // could be more then one, but for now, just one
	
	glEnable(texData.textureTarget);
	
	glBindTexture(texData.textureTarget, (GLuint)texData.textureID);
	
	glTexParameterf(texData.textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_WRAP_T, GL_NEAREST);
	
#ifndef TARGET_OPENGLES
	// can't do this on OpenGL ES: on full-blown OpenGL, 
	// internalGlDataType and glDataType (GL_LUMINANCE below)
	// can be different; on ES they must be exactly the same.
	//		glTexImage2D(texData.textureTarget, 0, texData.glTypeInternal, (GLint)texData.tex_w, (GLint)texData.tex_h, 0, GL_LUMINANCE, PIXEL_TYPE, 0);  // init to black...
#else
	glTexImage2D(texData.textureTarget, 0, texData.glTypeInternal, texData.tex_w, texData.tex_h, 0, texData.glTypeInternal, GL_UNSIGNED_BYTE, 0);
#endif
	
	
	
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glDisable(texData.textureTarget);
	
	texData.width = w;
	texData.height = h;
	texData.bFlipTexture = false;
	texData.bAllocated = true;
}
