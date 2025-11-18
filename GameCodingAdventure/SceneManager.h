#pragma once
class SceneManager
{
	DECLARE_SINGLETON(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

	void ChangeScene(SceneType sceneType);

private:
	class Scene* _scene;
	SceneType _sceneType = SceneType::None;
};

