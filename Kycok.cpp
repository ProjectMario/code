int main()
{
	vector <Enemy> Enemies;
	View view(Vector2f(170.0f, 96.0f), Vector2f(340.0f, 192.0f));
  RenderWindow window(VideoMode(340, 192), "Mario");

  Texture animationTexture;
  animationTexture.loadFromFile("image/Animation.png");

	Texture mapTexture;
  mapTexture.loadFromFile("image/MapBack.png");
	Player player(animationTexture, mapTexture);
	Image mapImage;
	mapImage.loadFromFile("image/SpriteList.png");
  Texture map;
  map.loadFromImage(mapImage);
	Sprite mapSprite;
	mapSprite.setTexture(map);

	Texture animationOfEnemy;
	animationOfEnemy.loadFromFile("image/Enemy.png");
	Enemies.push_back(Enemy(animationOfEnemy, 560, 145));
	Enemies.push_back(Enemy(animationOfEnemy, 1150, 145));
	Enemies.push_back(Enemy(animationOfEnemy, 1050, 145));
	Enemies.push_back(Enemy(animationOfEnemy, 660, 145));

	sf::Music music;
	music.openFromFile("music.ogg");
	music.play();

	 sf::Font font;
	 if(!font.loadFromFile("Fonts/OpenSans.ttf"))
	 {
		 cout << "Error" << endl;
	 }
	 sf::Text dieText;
	 dieText.setFont(font);
	 dieText.setCharacterSize(50);
	 dieText.setFillColor(sf::Color::Red);
	 dieText.setString("YOU DIE");
	 sf::Text text;
	 text.setFont(font);
	 text.setCharacterSize(12);
	 text.setFillColor(sf::Color::Black);
	 text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	 //text.setPosition(view.getCenter(), view.getCenter() );

  Clock clock;

  while (window.isOpen())
  {
      float time = clock.getElapsedTime().asMicroseconds();
      clock.restart();
      time = time / 800;

      Event event;
      while(window.pollEvent(event))
      {
          if(event.type == Event::Closed)
              window.close();
      }
			if(player.isLife)
			{
        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
          player.coorX = -0.1;
					player.direction = false;
          player.setPlayerCoordForView(view);
        }
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
          player.coorX = 0.1;
					player.direction = true;
          player.setPlayerCoordForView(view);
        }
        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
          if(player.onGround)
          {
            player.coorY = -0.3;
            player.onGround = false;
          }
          player.setPlayerCoordForView(view);
        }
		  }
			else
			{

			}
      player.update(time);
			for(unsigned int i = 0; i < Enemies.size(); i++)
				Enemies.at(i).update(time);
			for(unsigned int i = 0; i < Enemies.size(); i++)
			{
				if(player.rect.intersects(Enemies.at(i).rect))
				{
				 if(Enemies.at(i).isLife == true)
				 {
					 if(player.coorY > 0)
					 {
						 player.coorY = -0.2;
						 Enemies.at(i).x = 0;
						 Enemies.at(i).isLife = false;
					 }
					 else
					 {
						 player.animation.setColor(Color::Red);
						 player.isLife = false;
						 window.draw(dieText);
					 }
				 }
			  }
			}
			window.setView(view);
      window.clear();
			window.draw(player.rectMap);
			for(int i = 0 ; i < 12 ; i++)
			{
		    for(int j = 0 ; j < 100 ; j++)
				{
		      if(player.TileMap[i][j] == 'G')
					{
						mapSprite.setTextureRect(IntRect(34, 0, 16, 16));
					}
					if(player.TileMap[i][j] == 'B')
					{
						mapSprite.setTextureRect(IntRect(0, 0, 16, 16));
					}
					if(player.TileMap[i][j] == '1')
					{
						mapSprite.setTextureRect(IntRect(0, 17, 16, 16));
					}
					if(player.TileMap[i][j] == '2')
					{
						mapSprite.setTextureRect(IntRect(17, 17, 16, 16));
					}
					if(player.TileMap[i][j] == '3')
					{
						mapSprite.setTextureRect(IntRect(34, 17, 16, 16));
					}
					if(player.TileMap[i][j] == '4')
					{
						mapSprite.setTextureRect(IntRect(51, 17, 16, 16));
					}
					if(player.TileMap[i][j] == 'L')
				 	{
						mapSprite.setTextureRect(IntRect(17, 0, 16, 16));
					}
					if(player.TileMap[i][j] == 'C')
				 	{
						mapSprite.setTextureRect(IntRect(51, 0, 8, 8));
					}
		      if(player.TileMap[i][j] == ' ')
					 continue;

		      mapSprite.setPosition(j*16, i*16);
		      window.draw(mapSprite);
		    }
			}
			for(unsigned int i = 0; i < Enemies.size(); i++)
				window.draw(Enemies.at(i).enemySprite);
			window.draw(player.animation);
			std::ostringstream playerScoreS;
			playerScoreS << player.score;
			text.setString("Scores: " + playerScoreS.str());
			window.draw(text);
      window.display();

  }

  return 0;
}
