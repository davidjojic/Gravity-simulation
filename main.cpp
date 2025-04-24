#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class izvorGravitacje {
private:
	sf::Vector2f poz;
	float streanth;
	sf::CircleShape pl;
public:
	izvorGravitacje(float poz_x, float poz_y, float streanth)
	{
		poz.x = poz_x;
		poz.y = poz_y;
		this->streanth = streanth;
		pl.setFillColor(sf::Color::White);
		pl.setRadius(10);
		pl.setPosition(poz);
	}
	void render(sf::RenderWindow& window)
	{
		window.draw(pl);
	}
	sf::Vector2f get_poz()
	{
		return poz;
	}
	float get_str()
	{
		return streanth;
	}
};
sf::Color some_color(float k)
{
	if (k < 0.0) k = 0;
	else if (k > 1.0) k = 1;
	int r = 0, g = 0, b = 0;
	if (k < 0.5)
	{
		b = 255 *(1.f - 2 * k);
		g = 255 * 2*k;
	}
	else {
		g = 255 * (2.f - 2 * k);
		r = 255 - (2*k-1);
	}
	return sf::Color(r, g, b);
}
class cest {
private:
	sf::Vector2f poz;
	sf::Vector2f val;
	sf::CircleShape cl;
public:
	cest(float poz_x, float poz_y,float val_x, float val_y)
	{
		poz.x = poz_x;
		poz.y = poz_y;
		val.x = val_x;
		val.y = val_y;
		cl.setRadius(5);
		
	}
	void render(sf::RenderWindow& window)
	{
		cl.setPosition(poz);
		window.draw(cl);
	}
	sf::Vector2f get_poz()
	{
		return poz;
	}
	void updatepshy(izvorGravitacje& pl)
	{
		float dx = pl.get_poz().x - poz.x;
		float dy =pl.get_poz().y - poz.y;
		float dis = sqrt(dx * dx + dy * dy);

		float in_dis = 1.f / dis;
		float nor_dx = in_dis * dx;
		float nor_dy = in_dis * dy;
		float in_dis_sq = in_dis * in_dis;
		float accel_x = nor_dx * pl.get_str() * in_dis_sq;
		float accel_y = nor_dy * pl.get_str() * in_dis_sq;
		val.x += accel_x;
		val.y += accel_y;
		poz.x += val.x;
		poz.y += val.y;
	}
	void setcol(sf::Color x)
	{
		cl.setFillColor(x);
	}
};
int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 1000), "GRAVITACIJA", sf::Style::Default);
	window.setFramerateLimit(60);
	vector<izvorGravitacje> planeta;
	planeta.push_back(izvorGravitacje(500,500,7000));
	planeta.push_back(izvorGravitacje(1200,500,7000));
	int numcestica = 2000;
	vector<cest> cestica;
	for (int i = 0;i < numcestica;i++)
	{
		cestica.push_back(cest(600, 700, 4, 0.2 + ((double)1 / numcestica) * i));
		float k = (float)i / (float)numcestica;
		sf::Color ne = some_color(k);
		cestica[i].setcol(ne);
	}
	while (window.isOpen())
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		for(int i =0;i<planeta.size();i++)
		{
			for (int j = 0;j < cestica.size();j++)
			{
				cestica[j].updatepshy(planeta[i]);
			}
		}
			for (int j = 0;j < cestica.size();j++)
			{
				cestica[j].render(window);
			}
			for (int i = 0;i < planeta.size();i++)
			{
				
				planeta[i].render(window);
			}
		
		window.display();
	}
}
