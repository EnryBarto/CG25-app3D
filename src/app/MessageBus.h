#pragma once

class MessageBus {

	public:
		void aspectRatioChanged(float newAspectRatio);
		bool isAspectRatioChanged();
		float getNewAspectRatio();

	private:
		bool _aspectRatioChanged = false;
		float newAspectRatio;
};