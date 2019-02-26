#pragma once

class Pixel
{
private:
	int _red_value, _green_value, _blue_value;
	bool _is_populated;

public:
	// default constructor
	Pixel()
	{
		_red_value = NULL;
		_green_value = NULL;
		_blue_value = NULL;
		_is_populated = false;
	}

	// constructor for all values
	Pixel(int r_val, int g_val, int b_val)
	{
		_red_value = r_val;
		_green_value = g_val;
		_blue_value = b_val;
		_is_populated = true;
	}

	// getters for RGB values
	int getRedValue()
	{
		return _red_value;
	}
	int getGreenValue()
	{
		return _green_value;
	}
	int getBlueValue()
	{
		return _blue_value;
	}

	// get full status
	bool isPopulated()
	{
		return _is_populated;
	}

	// setters for RGB values
	void setRedValue(int r_val)
	{
		_red_value = r_val;
		_is_populated = true;
	}
	void setGreenValue(int g_val)
	{
		_green_value = g_val;
		_is_populated = true;
	}
	void setBlueValue(int b_val)
	{
		_blue_value = b_val;
		_is_populated = true;
	}

	// resets the pixel
	void clear()
	{
		Pixel();
	}
};