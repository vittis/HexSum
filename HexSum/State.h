#ifndef STATE_H_
#define STATE_H_

#include "GameObject.h"
#include "Hexsum/UIElement.h"
#include "SDL.h"
#include <vector>
#include <memory>

class State {
	protected:
		bool quitRequested;
		bool popRequested;
		std::vector<std::unique_ptr<GameObject>> objectArray;
		std::vector<std::unique_ptr<UIElement>> UIArray;
		virtual void UpdateUIArray(float);
		virtual void RenderUIArray();
		virtual void UpdateArray(float);
		virtual void RenderArray();


	public:

		State();
		virtual ~State();

		bool QuitRequested();
		bool PopRequested();

		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Update(float) = 0;
		virtual void Render() = 0;

		virtual void AddUIElement(UIElement*);
		virtual void AddObject(GameObject*);
};

#endif /* STATE_H_ */
