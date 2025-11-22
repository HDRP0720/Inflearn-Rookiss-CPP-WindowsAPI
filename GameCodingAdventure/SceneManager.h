#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLETON(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

	void ChangeScene(SceneType sceneType);

	Scene* GetCurrentScene() { return _currentScene; }

private:
	Scene* _currentScene;
	SceneType _sceneType = SceneType::None;
};

