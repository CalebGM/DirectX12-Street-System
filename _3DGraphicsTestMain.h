#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"


// Renders Direct3D content on the screen.
namespace _3DGraphicsTest
{
	class _3DGraphicsTestMain
	{
	public:
		_3DGraphicsTestMain();
		void CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void Update();
		bool Render();

		void OnWindowSizeChanged();
		void OnSuspending();
		void OnResuming();
		void OnDeviceRemoved();
		std::vector<GameObject^> RenderObjects() { return m_renderObjects; }

	private:
		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;

		// Rendering loop timer.
		DX::StepTimer				m_timer;
		std::vector<GameObject^>	m_renderObjects;
	};
}