//
// Created by ByteFlow on 2019/7/9.
//

#include <TriangleSample.h>
#include <TextureMapSample.h>
#include <NV21TextureMapSample.h>
#include <VaoSample.h>
#include "MyGLRenderContext.h"
#include "LogUtil.h"

MyGLRenderContext* MyGLRenderContext::m_pContext = nullptr;

MyGLRenderContext::MyGLRenderContext()
{
	m_pCurSample = new TriangleSample();
	m_pBeforeSample = nullptr;

}

MyGLRenderContext::~MyGLRenderContext()
{
	if (m_pCurSample)
	{
		delete m_pCurSample;
		m_pCurSample = nullptr;
	}

	if (m_pBeforeSample)
	{
		delete m_pBeforeSample;
		m_pBeforeSample = nullptr;
	}

}


void MyGLRenderContext::SetParamsInt(int paramType, int value0, int value1)
{
	LOGCATE("MyGLRenderContext::SetParamsInt paramType = %d, value0 = %d, value1 = %d", paramType, value0, value1);

	if (paramType == SAMPLE_TYPE)
	{
		m_pBeforeSample = m_pCurSample;

		LOGCATE("MyGLRenderContext::SetParamsInt 0 m_pBeforeSample = %p", m_pBeforeSample);

		switch (value0)
		{
			case SAMPLE_TYPE_KEY_TRIANGLE:
				m_pCurSample = new TriangleSample();
				break;
			case SAMPLE_TYPE_KEY_TEXTURE_MAP:
                m_pCurSample = new TextureMapSample();
				break;
			case SAMPLE_TYPE_KEY_YUV_TEXTURE_MAP:
				m_pCurSample = new NV21TextureMapSample();
				break;
			case SAMPLE_TYPE_KEY_VAO:
				m_pCurSample = new VaoSample();
				break;
			case SAMPLE_TYPE_KEY_FBO:
				break;
			case SAMPLE_TYPE_KEY_FBO_LEG_LENGTHEN:
				break;
			case SAMPLE_TYPE_KEY_COORD_SYSTEM:
				break;
			case SAMPLE_TYPE_KEY_BASIC_LIGHTING:
				break;
			case SAMPLE_TYPE_KEY_TRANSFORM_FEEDBACK:
				break;
			case SAMPLE_TYPE_KEY_MULTI_LIGHTS:
				break;
			case SAMPLE_TYPE_KEY_DEPTH_TESTING:
				break;
			case SAMPLE_TYPE_KEY_INSTANCING:
				break;
			case SAMPLE_TYPE_KEY_STENCIL_TESTING:
				break;
			case SAMPLE_TYPE_KEY_BLENDING:
				break;
			case SAMPLE_TYPE_KEY_PARTICLES:
				break;
			case SAMPLE_TYPE_KEY_SKYBOX:
				break;
			case SAMPLE_TYPE_KEY_3D_MODEL:
				break;
			case SAMPLE_TYPE_KEY_PBO:
				break;
            case SAMPLE_TYPE_KEY_BEATING_HEART:
                break;
            case SAMPLE_TYPE_KEY_CLOUD:
                break;
			case SAMPLE_TYPE_KEY_TIME_TUNNEL:
				break;
			case SAMPLE_TYPE_KEY_BEZIER_CURVE:
				break;
            case SAMPLE_TYPE_KEY_BIG_EYES:
                break;
			case SAMPLE_TYPE_KEY_FACE_SLENDER:
				break;
			case SAMPLE_TYPE_KEY_BIG_HEAD:
				break;
			case SAMPLE_TYPE_KEY_RATARY_HEAD:
				break;
			case SAMPLE_TYPE_KEY_VISUALIZE_AUDIO:
				break;
			case SAMPLE_TYPE_KEY_SCRATCH_CARD:
				break;
            case SAMPLE_TYPE_KEY_AVATAR:
                break;
			case SAMPLE_TYPE_KEY_SHOCK_WAVE:
				break;
			default:
			    m_pCurSample = nullptr;
				break;
		}

		LOGCATE("MyGLRenderContext::SetParamsInt m_pBeforeSample = %p, m_pCurSample=%p", m_pBeforeSample, m_pCurSample);
	}
}

void MyGLRenderContext::SetParamsFloat(int paramType, float value0, float value1) {
	LOGCATE("MyGLRenderContext::SetParamsFloat paramType=%d, value0=%f, value1=%f", paramType, value0, value1);
	if(m_pCurSample)
	{
		switch (paramType)
		{
			case SAMPLE_TYPE_KEY_SET_TOUCH_LOC:
				m_pCurSample->SetTouchLocation(value0, value1);
				break;
			case SAMPLE_TYPE_SET_GRAVITY_XY:
                m_pCurSample->SetGravityXY(value0, value1);
				break;
			default:
				break;

		}
	}

}

void MyGLRenderContext::SetParamsShortArr(short *const pShortArr, int arrSize) {
	LOGCATE("MyGLRenderContext::SetParamsShortArr pShortArr=%p, arrSize=%d, pShortArr[0]=%d", pShortArr, arrSize, pShortArr[0]);
	if(m_pCurSample)
	{
		m_pCurSample->LoadShortArrData(pShortArr, arrSize);
	}

}

void MyGLRenderContext::UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY)
{
	LOGCATE("MyGLRenderContext::UpdateTransformMatrix [rotateX, rotateY, scaleX, scaleY] = [%f, %f, %f, %f]", rotateX, rotateY, scaleX, scaleY);
	if (m_pCurSample)
	{
		m_pCurSample->UpdateTransformMatrix(rotateX, rotateY, scaleX, scaleY);
	}
}

void MyGLRenderContext::SetImageDataWithIndex(int index, int format, int width, int height, uint8_t *pData)
{
	LOGCATE("MyGLRenderContext::SetImageDataWithIndex index=%d, format=%d, width=%d, height=%d, pData=%p", index, format, width, height, pData);
	NativeImage nativeImage;
	nativeImage.format = format;
	nativeImage.width = width;
	nativeImage.height = height;
	nativeImage.ppPlane[0] = pData;

	switch (format)
	{
		case IMAGE_FORMAT_NV12:
		case IMAGE_FORMAT_NV21:
			nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
			break;
		case IMAGE_FORMAT_I420:
			nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
			nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
			break;
		default:
			break;
	}

	if (m_pCurSample)
	{
		m_pCurSample->LoadMultiImageWithIndex(index, &nativeImage);
	}

}

void MyGLRenderContext::SetImageData(int format, int width, int height, uint8_t *pData)
{
	LOGCATE("MyGLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p", format, width, height, pData);
	NativeImage nativeImage;
	nativeImage.format = format;
	nativeImage.width = width;
	nativeImage.height = height;
	nativeImage.ppPlane[0] = pData;

	switch (format)
	{
		case IMAGE_FORMAT_NV12:
		case IMAGE_FORMAT_NV21:
			nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
			break;
		case IMAGE_FORMAT_I420:
			nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
			nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
			break;
		default:
			break;
	}

	if (m_pCurSample)
	{
		m_pCurSample->LoadImage(&nativeImage);
	}

}

void MyGLRenderContext::OnSurfaceCreated()
{
	LOGCATE("MyGLRenderContext::OnSurfaceCreated");
	glClearColor(1.0f,1.0f,1.0f, 1.0f);
}

void MyGLRenderContext::OnSurfaceChanged(int width, int height)
{
	LOGCATE("MyGLRenderContext::OnSurfaceChanged [w, h] = [%d, %d]", width, height);
	glViewport(0, 0, width, height);
	m_ScreenW = width;
	m_ScreenH = height;
}

void MyGLRenderContext::OnDrawFrame()
{
	LOGCATE("MyGLRenderContext::OnDrawFrame");
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	if (m_pBeforeSample)
	{
		m_pBeforeSample->Destroy();
		delete m_pBeforeSample;
		m_pBeforeSample = nullptr;
	}

	if (m_pCurSample)
	{
		m_pCurSample->Init();
		m_pCurSample->Draw(m_ScreenW, m_ScreenH);
	}
}

MyGLRenderContext *MyGLRenderContext::GetInstance()
{
	LOGCATE("MyGLRenderContext::GetInstance");
	if (m_pContext == nullptr)
	{
		m_pContext = new MyGLRenderContext();
	}
	return m_pContext;
}

void MyGLRenderContext::DestroyInstance()
{
	LOGCATE("MyGLRenderContext::DestroyInstance");
	if (m_pContext)
	{
		delete m_pContext;
		m_pContext = nullptr;
	}

}



