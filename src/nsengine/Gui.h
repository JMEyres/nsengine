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
		void EnableAsTimer(bool _toggle);

		/// @brief Get the timer in seconds
		/// @return Seconds value of timer
		float GetTimer();

		/// @brief Set the timer to a specific value
		/// @param value Time for the timer to display
		void SetTimer(float _value);
		
		/// @brief Used to set the position of the on screen text element
		/// @param _pos Position in pixels on the screen
		void SetPosition(rend::vec3 _pos);

		/// @brief Set the resolution of the onscreen gui/Canvas
		/// @param _width Width of the window
		/// @param _height Height of the window
		void SetResolution(float _width, float _height);
	private:
		sys::string path = "./Resources/Fonts/Comic.png";
		sys::string text = "2D/OrthoGraphic";
		float frameTimer;
		bool timer;
		rend::vec3 position = rend::vec3(100, 100, 0);
		float resW = 1152.0f;
		float resH = 864.0f;
	};
}