#include<Siv3D.hpp>

void Main()
{
	Window::SetStyle(WindowStyle::Sizable);
	const Array<String> indices = Range(0, (Gamepad.MaxPlayerCount - 1)).map(Format);
	size_t playerIndex = 0;

	double t = 0;
	constexpr double keika = 0.0166;

	double v_x = 0;
	double v_y = 0;
	double wheel_r = 0.05;

	double T_f = 0;
	double T_rl = 0;
	double T_rl_x = 0;
	double T_rl_y = 0;
	double T_rr = 0;
	double T_rr_x = 0;
	double T_rr_y = 0;

	Vec2 zahyo = { 960,400 };

	while (System::Update())
	{
		t += Scene::DeltaTime();

		Triangle{ zahyo,300 }
		.drawFrame(2, Palette::White);

		Line{ zahyo.x,zahyo.y - 170,zahyo.x + T_f * 5,zahyo.y - 170 }
		.drawArrow(1, Vec2{ 7, 7 }, Palette::Skyblue);

		Line{ zahyo.x - 150,zahyo.y + 85,zahyo.x - 150 + T_rl_x * 5,zahyo.y + 85 - T_rl_y * 5 }
		.drawArrow(1, Vec2{ 7, 7 }, Palette::Skyblue);

		Line{ zahyo.x + 150,zahyo.y + 85,zahyo.x + 150 + T_rr_x * 5,zahyo.y + 85 - T_rr_y * 5 }
		.drawArrow(1, Vec2{ 7, 7 }, Palette::Skyblue);

		Line{ zahyo,zahyo.x + (T_rl_x + T_rr_x) * 5,zahyo.y - (T_rl_y + T_rr_y) * 5 }
		.drawArrow(3, Vec2{ 10,10 }, Palette::Red);

		zahyo.x = zahyo.x + T_rl_x + T_rr_x;
		zahyo.y = zahyo.y - (T_rl_y + T_rr_y);
		if (keika <= t)
		{
			t -= keika;

			if (const auto gamepad = Gamepad(playerIndex))
			{
				for (auto [i, axe] : Indexed(gamepad.axes))
				{
					ClearPrint();

					if (i == 0 && (axe > 0.05 || axe < -0.05))
					{
						v_x = (axe) / 2;

					}
					else if (i == 0 && (axe < 0.05 || axe > -0.05))
					{
						v_x = 0;
					}
					if (i == 1 && (axe > 0.05 || axe < -0.05))
					{
						v_y = -(axe) / 2;

					}
					else if (i == 1 && (axe < 0.05 || axe > -0.05))
					{
						v_y = 0;
					}

					T_f = (1 / wheel_r) * (v_x);
					T_rl = (1 / wheel_r) * ((v_x / -1.414) - (v_y / -1.414));
					T_rr = (1 / wheel_r) * ((v_x / 1.414) + (v_y / 1.414));

					T_rl_x = T_rl / -1.414;
					T_rl_y = T_rl / 1.414;
					T_rr_x = T_rr / 1.414;
					T_rr_y = T_rr / 1.414;

					Print << U"vx : {}"_fmt(v_x);
					Print << U"vy : {}\n\n\n"_fmt(v_y);

					Print << U"T_f = {}rad/s\n"_fmt(T_f);
					Print << U"T_rl = {}rad/s\n"_fmt(T_rl);
					Print << U"T_rr = {}rad/s"_fmt(T_rr);
				}
			}
		}

	}
}
