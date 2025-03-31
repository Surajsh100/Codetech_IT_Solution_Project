#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<deque>
#include<ctime>

const int CELL_SIZE=20;
const int WIDTH=30;
const int HEIGHT=20;
const int WINDOW_WIDTH=WIDTH*CELL_SIZE;
const int WINDOW_HEIGHT=HEIGHT*CELL_SIZE;

enum Direction {UP , DOWN , LEFT , RIGHT}; 

struct SnakeSegment
{
    int x,y;
    SnakeSegment(int x, int y) : x(x), y(y){}
};

class SnakeGame
{
    private:
    sf :: RenderWindow window;
    std :: deque<SnakeSegment> snake;
    Direction direction;
    bool isAlive;
    sf :: Vector2i food;
    sf :: Clock clock;
    float speed;
    int score;
    sf :: Font font;
    sf :: Text scoreText;
    sf :: SoundBuffer eatBuffer , gameOverBuffer;
    sf :: Sound eatSound , gameOverSound;
    sf :: Texture backgroundTexture;
    sf :: Sprite background;

    public:
    SnakeGame()
         :window(sf :: VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Snake Game"), direction(RIGHT), isAlive(true), speed(0.15f), score(0)
        {
            snake.push_back(SnakeSegment(WIDTH / 2, HEIGHT / 2));
            placeFood();
        
        // Load font
        font.loadFromFile("arial.ttf");
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf :: Color :: White);
        scoreText.setPosition(10, 10);

        //Load sound effects
        eatBuffer.loadFromFile("eat.wav");
        gameOverBuffer.loadFromFile("gameOver.wav");
        eatSound.setBuffer(eatBuffer);
        gameOverSound.setBuffer(gameOverBuffer);

        //Load background
        backgroundTexture.loadFromFile("background.png");
        background.setTexture(backgroundTexture);
    }
    void placeFood()
    {
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
    }
    void handleInput()
    {
        if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Up)&& direction != DOWN) direction = UP;
        if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Down)&& direction != UP) direction = DOWN;
        if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left)&& direction != RIGHT) direction = LEFT;
        if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right)&& direction != LEFT) direction = RIGHT;
    }
    void update()
    {
        if(clock.getElapsedTime().asSeconds() < speed)return;
        clock.restart();
        if(!isAlive)
        return;
        SnakeSegment head = snake.front();
        switch(direction)
        {
            case UP: head.y--; break;
            case DOWN: head.y++; break;
            case LEFT: head.x--; break;
            case RIGHT: head.x++; break;
        }
        for(size_t i=1; i < snake.size();i++)
        {
            if(head.x == snake[i].x && head.y == snake[i].y)
        //if(head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT)
            {
                isAlive = false;
                gameOverSound.play();
                return;
            }
        }
        snake.push_front(head);
        if(head.x == food.x && head.y == food.y)
        {
            placeFood();
            eatSound.play();
            score +=10;
            speed *= 0.95;
        }
        else
        {
            snake.pop_back();
        }
    }
    void render()
    {
        window.clear();
        window.draw(background);

        sf :: RectangleShape shape(sf :: Vector2f (CELL_SIZE, CELL_SIZE));
        shape.setFillColor(sf :: Color :: Green);
        for(const auto & segment : snake)
        {
            shape.setPosition(segment.x * CELL_SIZE , segment.y *CELL_SIZE);
            window.draw(shape);
        }
        shape.setFillColor(sf :: Color :: Red);
        shape.setPosition(food.x * CELL_SIZE, food.y* CELL_SIZE);
        window.draw(shape);

        scoreText.setString("Score : " + std :: to_string(score));
        window.draw(scoreText);

        window.display();
    }
    void run()
    {
        while(window.isOpen())
        {
            sf :: Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf :: Event :: Closed)
                     window.close();
            }
            handleInput();
            update();
            render();
        }
    }
};
int main()
{
    srand(static_cast<unsigned> (time(0)));
    SnakeGame game;
    game.run();
    return 0; 
}