#pragma once

class FVector2D
{
public:
	float X = 0.0f;
	float Y = 0;

	static const FVector2D ZERO;
	static const FVector2D LEFT;
	static const FVector2D RIGHT;
	static const FVector2D UP;
	static const FVector2D DOWN;

	FVector2D()
	{

	}

	FVector2D(float _X, float _Y) : X(_X), Y(_Y)
	{

	}

	FVector2D(int _X, int _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
	{

	}

	FVector2D(long _X, long _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
	{

	}

	//X값을 int로 바꿔주는 함수
	int iX() const
	{
		return static_cast<int>(X);
	}

	//Y값을 int로 바꿔주는 함수
	int iY() const
	{
		return static_cast<int>(Y);
	}

	// X든 Y든 0이있으면 터트리는 함수.
	bool IsZeroed() const
	{
		return X == 0.0f || Y == 0.0f;
	}

	// 값을 절반으로 바꿔주는 함수
	FVector2D Half() const
	{
		return { X * 0.5f, Y * 0.5f };
	}

	FVector2D operator*(float _Value) const
	{
		FVector2D Result;
		Result.X = X * _Value;
		Result.Y = Y * _Value;
		return Result;
	}



	FVector2D operator+(FVector2D _Other) const
	{
		FVector2D Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FVector2D operator-(FVector2D _Other) const
	{
		FVector2D Result;
		Result.X = X - _Other.X;
		Result.Y = Y - _Other.Y;
		return Result;
	}


	FVector2D operator/(int _Value) const
	{
		FVector2D Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}


	bool operator==(FVector2D _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	bool EqualToInt(FVector2D _Other) const
	{
		return iX() == _Other.iX() && iY() == _Other.iY();
	}

	FVector2D& operator+=(FVector2D _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}

	//X와Y의 값을 문자열로 표현해주는 함수
	std::string ToString()
	{
		std::string Stream;

		Stream += "X : [";
		Stream += std::to_string(X);
		Stream += "] Y : [";
		Stream += std::to_string(Y);
		Stream += "]";
		return Stream;
	}
};

class FTransform
{
public:
	FVector2D Scale;
	FVector2D Location;

	// 왼쪽위
	FVector2D CenterLeftTop() const
	{
		return Location - Scale.Half();
	}

	//오른쪽아래
	FVector2D CenterRightBottom() const
	{
		return Location + Scale.Half();
	}
};


class FIntPoint
{
public:
	int X = 0;
	int Y = 0;

	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;

	FIntPoint()
	{

	}

	FIntPoint(int _X, int _Y) : X(_X), Y(_Y)
	{

	}

	FIntPoint operator+(FIntPoint _Other) const
	{
		FIntPoint Result; 
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FIntPoint operator/(int _Value) const
	{
		FIntPoint Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}


	bool operator==(FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	FIntPoint& operator+=(FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}


};

class EngineMath
{
};

class UColor
{
public:
	union
	{
		int Color;
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
	};

	UColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}
};