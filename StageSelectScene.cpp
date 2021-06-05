#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "PlayScene.hpp"
#include "SettingScene.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include "Slider.hpp"
#include "StageSelectScene.hpp"

void StageSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    Engine::ImageButton* btn;

	// Stage 1 Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Stage 1", "pirulen.ttf", 48, halfW, halfH / 2, 0, 0, 0, 255, 0.5, 0.5));

	// Stage 2 Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Stage 2", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    
	// Setting Button
	btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", w - 220, h - 70, 200, 50);
	btn->SetOnClickCallback(std::bind(&StageSelectScene::SettingOnClick, this, 1));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Setting", "pirulen.ttf", 24, w - 120 , h - 50, 0, 0, 0, 255, 0.5, 0.5));

	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void StageSelectScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void StageSelectScene::PlayOnClick(int stage) {
	PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
	scene->MapId = stage;
	Engine::GameEngine::GetInstance().ChangeScene("play");
}
void StageSelectScene::SettingOnClick(int stage) {
	//SettingScene* scene = dynamic_cast<SettingScene*>(Engine::GameEngine::GetInstance().GetScene("setting"));
	Engine::GameEngine::GetInstance().ChangeScene("setting");
}
