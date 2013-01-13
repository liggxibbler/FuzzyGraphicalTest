////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <time.h>

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	m_fis = new Fuzzy::FIS_Init;
	m_fis->Initialize();

	m_setPoint[0] = 0.0;
	m_setPoint[1] = 0.1;

	m_input[0] = -1.0f;
	m_input[1] = 0.0f;

	
	m_Road = new ModelClass;
	if(!m_Road)
	{
		return false;
	}
	result = m_Road->Initialize(m_D3D->GetDevice(), "../data/bill.txt", L"../data/road.png", NULL);	
	if(!result)
	{
		return false;
	}

	m_Car = new ModelClass;
	if(!m_Car)
	{
		return false;
	}
	result = m_Car->Initialize(m_D3D->GetDevice(), "../data/bill.txt", L"../data/car2.png", NULL);	
	if(!result)
	{
		return false;
	}

	// Create the bitmap shader object.
	m_BitmapShader = new BitmapShaderClass;
	if(!m_BitmapShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_BitmapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	if(m_BitmapShader)
	{
		m_BitmapShader->Shutdown();
		delete m_BitmapShader;
		m_BitmapShader = 0;
	}

	// Release the model object.
	if(m_Road)
	{
		m_Road->Shutdown();
		delete m_Road;
		m_Road = 0;
	}

	// Release the model object.
	if(m_Car)
	{
		m_Car->Shutdown();
		delete m_Car;
		m_Car = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(GraphicsClass::GraphicsUpdateInfo& guInf)
{
	bool result;
	static float time = 0.0f;
	static float dt;
	static float input[2];
	static float k = 100; //  Convert force to accelleration
						 // the greater K is, the smaller the mass of the car is assumed

	time += guInf.time;

	//m_Camera->Frame(guInf.mouseDiffX, guInf.mouseDiffY, guInf.wKey, guInf.aKey, guInf.sKey, guInf.dKey);

	dt = guInf.time / 1000.0f;

	if(guInf.dKey)
	{
		m_setPoint[0] += m_setPoint[1] * dt;
	}
	if(guInf.aKey)
	{
		m_setPoint[0] -= m_setPoint[1] * dt;
	}
	if(guInf.wKey)
	{
		m_setPoint[1] += .01;
	}
	if(guInf.sKey)
	{
		m_setPoint[1] -= .01;
	}

	input[0] = m_input[0] - m_setPoint[0];
	input[1] = m_input[1];

	m_force = m_fis->Evaluate(input)[0] * k;
	
	m_input[0] += m_input[1] * dt;
	m_input[1] += m_force * dt;


	// Render the graphics scene.
	result = Render(time);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float time)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	D3DXMATRIX cameraRot, temp;

	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);

	bool result;

	static float col = (m_input[0] + 1.0f) * .5f;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	
	m_D3D->TurnZBufferOff();
	//m_D3D->CullFrontFace();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//D3DXMatrixTranslation(&worldMatrix, 0.0, 0.0, .2f);
	//D3DXMatrixRotationY(&worldMatrix, time / 1000);
	//D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &temp);
	D3DXMatrixScaling(&worldMatrix, 2, 5, 0.0);
	D3DXMatrixTranslation(&temp, m_setPoint[0] * .5, 0.0, 0.0);
	D3DXMatrixMultiply(&worldMatrix, &temp, &worldMatrix);

	m_D3D->TurnAlphaBlendingOn();

	m_Road->Render(m_D3D->GetDeviceContext(), worldMatrix);

	result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Road->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		m_Road->GetTexture(), time / 1000.0f);
	if(!result)
	{
		return false;
	}

	
	//D3DXMatrixMultiply(&worldMatrix, &temp, &worldMatrix);

	D3DXMatrixTranslation(&worldMatrix, m_input[0] * 1, 0.0, 0.0);

	m_Car->Render(m_D3D->GetDeviceContext(), worldMatrix);

	result = m_BitmapShader->Render(m_D3D->GetDeviceContext(), m_Car->GetIndexCount(), viewMatrix, worldMatrix, projectionMatrix, 
		m_Car->GetTexture(), 0);
	if(!result)
	{
		return false;
	}


	//m_D3D->TurnAlphaBlendingOff();	

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}