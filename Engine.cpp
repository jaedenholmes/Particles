#include "Engine.h"
#include "Particle.h"

Engine::Engine()
{
	VideoMode vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	m_Window.create(vm, "Particles", Style::Default);
}

void Engine::run()
{
	Clock Clock;
	cout << "Starting Particle unit tests..." << endl;
	
	
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		Time time = Clock.restart();
		double seconds = time.asSeconds();
		input();
		update(seconds);
		draw();
	}
}
void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if(event.type == Event::Closed)
		{
			m_Window.close();
		}

		if (event.type == Event::MouseButtonPressed)
		{
			//to hold the mouse locations
			Vector2i mouseLocation = { event.mouseButton.x, event.mouseButton.y };


			if (Mouse::isButtonPressed(Mouse::Left))
			{
				//loop to create five particles at mouseclick location
				for (int i = 0; i < 5; i++)
				{
					//to create number of points between 25 and 50 
					int r = (rand() % (50 - 25 + 1)) + 25;
					Particle p(m_Window, r, mouseLocation);
					m_particles.push_back(p);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				m_Window.close();
			}
		}
	}
}
void Engine::update(float dtAsSeconds)
{
	vector<Particle>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end();)
	{
		if (iter->getTTL() > 0.0)
		{
			iter->update(dtAsSeconds);
			iter++;
		}
		else
		{
			iter = m_particles.erase(iter);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles[i]);
	}
	m_Window.display();
}
