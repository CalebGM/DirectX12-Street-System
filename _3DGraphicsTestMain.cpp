#include "pch.h"
#include "_3DGraphicsTestMain.h"
#include "Common\DirectXHelper.h"

using namespace _3DGraphicsTest;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

// The DirectX 12 Application template is documented at https://go.microsoft.com/fwlink/?LinkID=613670&clcid=0x409

// Loads and initializes application assets when the application is loaded.
_3DGraphicsTestMain::_3DGraphicsTestMain()
{
	m_trafficLight = ref new TrafficLightObject(XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 1.0f), "Red");
	m_gameObjects.push_back(m_trafficLight);
	m_trafficLightObjects.push_back(m_trafficLight);

	m_trafficLight = ref new TrafficLightObject(XMFLOAT3(7.0f, 0.0f, 0.0f), XMFLOAT3(7.0f, 0.0f, 1.0f), "Green");
	m_gameObjects.push_back(m_trafficLight);
	m_trafficLightObjects.push_back(m_trafficLight);
	
	m_car = ref new CarObject(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(20.0f, 0.0f, 0.0f));
	m_gameObjects.push_back(m_car);
	m_carObjects.push_back(m_car);
	
	m_car = ref new CarObject(XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT3(20.0f, 0.0f, 0.0f));
	m_gameObjects.push_back(m_car);
	m_carObjects.push_back(m_car);

	m_car = ref new CarObject(XMFLOAT3(-2.0f, 0.0f, 0.0f), XMFLOAT3(20.0f, 0.0f, 0.0f));
	m_gameObjects.push_back(m_car);
	m_carObjects.push_back(m_car);

	m_car = ref new CarObject(XMFLOAT3(-10.0f, 0.0f, 0.0f), XMFLOAT3(20.0f, 0.0f, 0.0f));
	m_gameObjects.push_back(m_car);
	m_carObjects.push_back(m_car);

	m_car = ref new CarObject(XMFLOAT3(-12.0f, 0.0f, 0.0f), XMFLOAT3(20.0f, 0.0f, 0.0f));
	m_gameObjects.push_back(m_car);
	m_carObjects.push_back(m_car);

	m_gameObjects.push_back(ref new RoadObject(XMFLOAT3(0.0f, -0.25f, 0.0f), XMFLOAT3(20.0f, -0.25f, 0.0f)));

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

// Creates and initializes the renderers.
void _3DGraphicsTestMain::CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	// TODO: Replace this with your app's content initialization.
	m_sceneRenderer = std::unique_ptr<Sample3DSceneRenderer>(new Sample3DSceneRenderer(deviceResources));
	m_sceneRenderer->ReceiveGameObjects(m_gameObjects);
	OnWindowSizeChanged();
}

// Updates the application state once per frame.
void _3DGraphicsTestMain::Update()
{
	// Update scene objects.
	m_timer.Tick([&]()
	{
		// TODO: Replace this with your app's content update functions.
		
		//m_sceneRenderer->Update(m_timer);
		m_angle += static_cast<float>(m_timer.GetElapsedSeconds() * 0.002);
		for (auto object = m_trafficLightObjects.begin(); object != m_trafficLightObjects.end(); object++)
		{
			(*object)->UpdateTime(m_timer.GetElapsedSeconds());
		}
		for (auto object = m_carObjects.begin(); object != m_carObjects.end(); object++)
		{
			bool accelerate = true;
			float carPosition = (*object)->Position().x;
			
			if (object != m_carObjects.begin())
			{
				auto object2 = object - 1;
				if (abs((*object2)->Position().x - carPosition) < 0.9)
				{
					(*object)->Stop();
					accelerate = false;
				}
				else if (abs((*object2)->Position().x - carPosition) < 1.3)
				{
					(*object)->SlowToStop();
					accelerate = false;
				}
			}
			

			auto trafficLight = m_trafficLightObjects.begin();
			while ((*trafficLight)->Position().x - carPosition < 0 && (trafficLight + 1) != m_trafficLightObjects.end())
			{
				trafficLight++;
			}

			double distance = (*trafficLight)->Position().x - carPosition;
			if (distance > 0)
			{
				if ((*trafficLight)->Color() == "Red")
				{
					if (distance < 1.2)
					{
						(*object)->Stop();
						accelerate = false;
					}
					else if (distance < 1.7)
					{
						(*object)->SlowToStop();
						accelerate = false;
					}
				}
				else if ((*trafficLight)->Color() == "Yellow" && distance < 1.7)
				{
					double ans = (*object)->Velocity().x * (*trafficLight)->TimeToRed() * m_timer.GetFramesPerSecond();
					if ((*object)->Velocity().x * (*trafficLight)->TimeToRed() * m_timer.GetFramesPerSecond() < distance)
					{
						(*object)->SlowToStop();
						accelerate = false;
					}
				}
			}
			
			
			if (accelerate)
			{
				(*object)->AccelerateToMax();
			}
			(*object)->Position((*object)->VectorPosition() + (*object)->VectorVelocity());
		}
	});
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool _3DGraphicsTestMain::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	// Render the scene objects.
	// TODO: Replace this with your app's content rendering functions.
	return m_sceneRenderer->Render();
}

// Updates application state when the window's size changes (e.g. device orientation change)
void _3DGraphicsTestMain::OnWindowSizeChanged()
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

// Notifies the app that it is being suspended.
void _3DGraphicsTestMain::OnSuspending()
{
	// TODO: Replace this with your app's suspending logic.

	// Process lifetime management may terminate suspended apps at any time, so it is
	// good practice to save any state that will allow the app to restart where it left off.

	m_sceneRenderer->SaveState();

	// If your application uses video memory allocations that are easy to re-create,
	// consider releasing that memory to make it available to other applications.
}

// Notifes the app that it is no longer suspended.
void _3DGraphicsTestMain::OnResuming()
{
	// TODO: Replace this with your app's resuming logic.
}

// Notifies renderers that device resources need to be released.
void _3DGraphicsTestMain::OnDeviceRemoved()
{
	// TODO: Save any necessary application or renderer state and release the renderer
	// and its resources which are no longer valid.
	m_sceneRenderer->SaveState();
	m_sceneRenderer = nullptr;
}
