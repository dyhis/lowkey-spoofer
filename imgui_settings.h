#include "imgui.h"

namespace ImStyle {

	inline ImVec4 general_color = ImColor(177, 156, 217, 255);

	namespace window {
		inline ImVec4 background_pic = ImColor(255, 255, 255, 120);

		inline ImVec4 background = ImColor(0, 0, 0, 200); // Negro
		inline ImVec4 border = ImColor(50, 50, 50, 255);

		inline ImVec4 shadow_text = ImColor(177, 156, 217, 150);
		inline ImVec4 shadow_panel = ImColor(177, 156, 217, 100);

		inline ImVec2 size = ImVec2(700, 480);
		inline float rounding = 15.f;
	}

	namespace button {

		inline ImVec4 background_active = ImColor(177, 156, 217,255);
		inline ImVec4 background_hov = ImColor(177, 156, 217, 235);
		inline ImVec4 background = ImColor(177, 156, 217, 205);

		inline ImVec4 background_shadow = ImColor(45, 45, 45, 205);

		inline float rounding = 5.f;
	}

	namespace input {

		inline ImVec4 text_selected = ImColor(56, 56, 56, 70);

		inline ImVec4 background_active = ImColor(177, 156, 217, 255);
		inline ImVec4 background_hov = ImColor(177, 156, 217, 235);
		inline ImVec4 background = ImColor(177, 156, 217, 205);

		inline float rounding = 5.f;
	}

	namespace checkbox {

		inline ImVec4 checkmark_active = ImColor(255, 255, 255, 235);
		inline ImVec4 checkmark_inactive = ImColor(255, 255, 255, 0);

		inline ImVec4 background_hov = ImColor(42, 45, 50, 235);
		inline ImVec4 background = ImColor(37, 42, 45, 205);

		inline float rounding = 5.f;
	}

	namespace text {

		inline ImVec4 hint_text = ImColor(0, 0, 0, 0);
		inline ImVec4 have_account = ImColor(255, 255, 255, 70);

		inline ImVec4 text_active = ImColor(255, 255, 255, 255);
		inline ImVec4 text_hov = ImColor(200, 200, 200, 255);
		inline ImVec4 text = ImColor(150, 150, 150, 255);

	}

	namespace selector {

		inline ImVec4 icon = ImColor(47, 50, 53, 230);

		inline ImVec4 background_active = ImColor(47, 50, 53, 150);
		inline ImVec4 background_hov = ImColor(41, 44, 47, 150);
		inline ImVec4 background = ImColor(35, 38, 41, 150);

	}

	namespace changelist {

		inline ImVec4 background_active = ImColor(47, 50, 53, 100);
		inline ImVec4 background_hov = ImColor(41, 44, 47, 100);
		inline ImVec4 background = ImColor(35, 38, 41, 100);

	}

}
