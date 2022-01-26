#pragma once

#ifdef GS_PLATFORM_WINDOWS

extern Genesis::Application* Genesis::CreateApplication();

int main(int argc, char** argv)
{
	Genesis::Log::Init();
	GS_CORE_WARN("Initialized Core Logger!");
	GS_INFO("Initialized Client Logger!");

	auto app = Genesis::CreateApplication();
	app->Run();
	delete app;
}

#endif
