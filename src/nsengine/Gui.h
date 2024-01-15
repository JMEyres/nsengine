#pragma once
#include "Component.h"
#include "Entity.h"
#include <rend/rend.h>
#include <sys/string.h>

namespace nsengine
{
	struct Camera;
	/// @brief Component handling on screen graphical user interface
	struct Gui : Component
	{
		void OnDisplay();

		/// @brief Set the path to chosen font
		/// @param _path String path to font
		void SetPath(sys::string _path);

		/// @brief Set the text to display to screen
		/// @param _text String of text
		void SetText(sys::string _text);

		/// @brief Sets the GUI text to be a timer
		/// @param toggle True/False of being a timer
		void EnableAsTimer(bool toggle);

		/// @brief Get the timer in seconds
		/// @return Seconds value of timer
		float GetTimer();

		/// @brief Set the timer to a specific value
		/// @param value Time for the timer to display
		void SetTimer(float value);
		
	private:
		sys::string path = "./Resources/Fonts/Comic.png";
		sys::string text = "2D/OrthoGraphic";
		float frameTimer;
		bool timer;
	};
}