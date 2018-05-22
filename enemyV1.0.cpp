class Enemy
{
	Sprite enemyAnimation;
	bool life = true;
	int x,y;
	Enemy(Texture &texture, int dx, int dy)
	{
		x = dx;
		y = dy;
		enemyAnimation.setTexture(texture);
		enemyAnimation.setTextureRect(IntRect(0, 0, 16, 16))
	}
	void update(float time)
	{
		if(life)
		{
			enemyAnimation.setTextureRect(IntRect(0, 18, 16, 16));
		}
		else
		{
			enemyAnimation.setTextureRect(IntRect(0, 18, 16, 16));
		}
	}
};
