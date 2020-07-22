#include <SFML/Graphics.hpp>
#include <iostream>
#include <Box2D/Box2D.h>
#include "physics.h"
#include <vector>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;


int main()
{
    RenderWindow window(VideoMode(320, 512), "Plinko?");
    window.setFramerateLimit(60);

    b2World world(b2Vec2(0.0,20.0));

////////////SCREEN VARIABLES//////////////////////////

bool playing = false;
bool mainmenu = true;
bool options = false;
bool waitwhat = false;

//////////////////////score?

int score = 0;

///////////////////////////////////////////////////////////Sounds//////////////////////////////////////////////

//play button
SoundBuffer bplay;
bplay.loadFromFile("play.wav");

Sound splay;
splay.setBuffer(bplay);

//drop
SoundBuffer bdrop;
bdrop.loadFromFile("drop.wav");

Sound sdrop;
sdrop.setBuffer(bdrop);

//hit
SoundBuffer bhit;
bhit.loadFromFile("hit.wav");

Sound hit;
hit.setBuffer(bhit);

//click1
SoundBuffer sbclick1;
sbclick1.loadFromFile("click.wav");

Sound click1;
click1.setBuffer(sbclick1);

//click2
SoundBuffer sbclick2;
sbclick2.loadFromFile("click2.wav");

Sound click02;
click02.setBuffer(sbclick2);


//////////////////////Color Ints/////////////

int a = 42;

int b = 224;

int c = 60;

/////////////////////////TEXTURES///////////////////////

    //points layer
    Texture points;
    points.loadFromFile("pointslayer.png");

    //backgrounds
    Texture wood;
    wood.loadFromFile("wood.jpg");

    Texture bricks;
    bricks.loadFromFile("bricks.jpg");

    Texture cf;
    cf.loadFromFile("CF.jpg");

    Texture electricity;
    electricity.loadFromFile("electricity.jpg");

    Texture fire;
    fire.loadFromFile("fire.jpg");

    Texture ice;
    ice.loadFromFile("ice.jpg");

    Texture metal;
    metal.loadFromFile("metal.jpg");

    Texture stone;
    stone.loadFromFile("stone.jpg");

    Texture water;
    water.loadFromFile("water.jpg");

    bool woodb = false;
    bool bricksb = false;
    bool cfb = true;
    bool electricityb = false;
    bool fireb = false;
    bool iceb = false;
    bool metalb = false;
    bool stoneb = false;
    bool waterb = false;

    bool blueb = false;
    bool cyanb = false;
    bool greenb = false;
    bool orangeb = false;
    bool pinkb = false;
    bool purpleb = false;
    bool redb = true;
    bool yellowb = false;

    //menu textures
    Texture menumain;
    menumain.loadFromFile("startscreen.png");

    Texture menumainp;
    menumainp.loadFromFile("startscreenplay.png");

    Texture menumaino;
    menumaino.loadFromFile("startscreenoptions.png");

    Texture menumainww;
    menumainww.loadFromFile("startscreenhowto.png");

    ////options textures
    //colors
    Texture optionsblue;
    optionsblue.loadFromFile("colorblue.png");

    Texture optionscyan;
    optionscyan.loadFromFile("colorcyan.png");

    Texture optionsgreen;
    optionsgreen.loadFromFile("colorgreen.png");

    Texture optionsorange;
    optionsorange.loadFromFile("colororange.png");

    Texture optionspink;
    optionspink.loadFromFile("colorpink.png");

    Texture optionspurple;
    optionspurple.loadFromFile("colorpurple.png");

    Texture optionsred;
    optionsred.loadFromFile("colorred.png");

    Texture optionsyellow;
    optionsyellow.loadFromFile("coloryellow.png");

    //background button
    Texture optionsbricks;
    optionsbricks.loadFromFile("BGbricks.png");

    Texture optionscf;
    optionscf.loadFromFile("BGcf.png");

    Texture optionselectricity;
    optionselectricity.loadFromFile("BGelectricity.png");

    Texture optionsfire;
    optionsfire.loadFromFile("BGfire.png");

    Texture optionsice;
    optionsice.loadFromFile("BGice.png");

    Texture optionsmetal;
    optionsmetal.loadFromFile("BGmetal.png");

    Texture optionsstone;
    optionsstone.loadFromFile("BGstone.png");

    Texture optionswater;
    optionswater.loadFromFile("BGwater.png");

    Texture optionswood;
    optionswood.loadFromFile("BGwood.png");

    //backbutton
    Texture optionsback;
    optionsback.loadFromFile("backbtn.png");

    Texture optionsbackbold;
    optionsbackbold.loadFromFile("backbtnbold.png");

    //howto
    Texture howtobtn;
    howtobtn.loadFromFile("howto.png");

    //restart
    Texture restartbtn;
    restartbtn.loadFromFile("restartbtn.png");

    Texture restartbtnbold;
    restartbtnbold.loadFromFile("restartbtnbold.png");

    //scores
    Texture onepoint;
    onepoint.loadFromFile("1points.png");

    Texture threepoint;
    threepoint.loadFromFile("3points.png");

    Texture fivepoints;
    fivepoints.loadFromFile("5points.png");

    Texture tenpoints;
    tenpoints.loadFromFile("10points.png");


////////////////////////////////////////////////SPRITES/////////////////////////////////

    //creating points layer sprite
    Sprite pointslayer;
    pointslayer.setTexture(points);
    pointslayer.setPosition(0,0);

    Sprite bg;
    bg.setTexture(cf);
    bg.setPosition(0,0);

    //menu
    Sprite menu;
    menu.setTexture(menumain);
    menu.setPosition(0,0);

    Sprite colors;
    colors.setTexture(optionsred);
    colors.setPosition(0,0);

    Sprite bgbutton;
    bgbutton.setTexture(optionsmetal);
    bgbutton.setPosition(0,0);

    Sprite backbtn;
    backbtn.setTexture(optionsback);
    backbtn.setPosition(0,0);

    Sprite howto;
    howto.setTexture(howtobtn);
    howto.setPosition(0,0);

    Sprite restart;
    restart.setTexture(restartbtn);
    restart.setPosition(0,0);

    Sprite scorez;
    scorez.setTexture(tenpoints);
    scorez.setPosition(0,0);

/////////////////////////////////////////////////////////


    vector<Block> pins;
    bool click = false;
    bool click2 = false;

    //walls
    Block wallleft = physics::createBox(world, -100, 0, 100, 512, b2_staticBody);
    Block wallright = physics::createBox(world, 320, 0, 100, 512, b2_staticBody);

    //funnels
    vector<Vector2f> funnel1;
    vector<Vector2f> funnel2;

    funnel1.push_back(Vector2f(0, 0));
    funnel1.push_back(Vector2f(0, 73));
    funnel1.push_back(Vector2f(30, 73));

    funnel2.push_back(Vector2f(0, 0));
    funnel2.push_back(Vector2f(0, 73));
    funnel2.push_back(Vector2f(-30, 73));

    Block trileft = physics::createPolygon(world, 0, 0, funnel1, b2_staticBody);
    Block triright = physics::createPolygon(world, 320, 0, funnel2, b2_staticBody);

    physics::setBlockColor(trileft, Color(226, 24, 24));
    physics::setBlockColor(triright, Color(226, 24, 24));

    //moving ball
    int hovx = 25;
    int hovmove = 2;
    bool hovering = true;

    CircleShape hoverball(11);
    hoverball.setFillColor(Color(a, b, c));
    hoverball.setPosition(hovx, 20);





    //8 rows starting at y=70 and add 50 each row

        for (int h = 0; h < 4; h++){
        pins.push_back(physics::createCircle(world, 80 + 53*h, 70, 3, b2_staticBody));
        physics::setBlockColor(pins.back(),Color(226, 24, 24));
        }

        for (int h = 0; h < 5; h++){
        pins.push_back(physics::createCircle(world, 53 + 53*h, 120, 3, b2_staticBody));
        physics::setBlockColor(pins.back(),Color(226, 67, 23));
        }

        for (int h = 0; h < 6; h++){
        pins.push_back(physics::createCircle(world, 27 + 53*h, 170, 3, b2_staticBody));
        physics::setBlockColor(pins.back(),Color(226, 144, 23));
        }

        for (int h = 0; h < 5; h++){
        pins.push_back(physics::createCircle(world, 53 + 53*h, 220, 3, b2_staticBody));
        physics::setBlockColor(pins.back(),Color(226, 198, 23));
        }

        for (int h = 0; h < 6; h++){
        pins.push_back(physics::createCircle(world, 27 + 53*h, 270, 3, b2_staticBody));
        physics::setBlockColor(pins.back(),Color(186, 226, 9));
        }

        for (int h = 0; h < 5; h++){
        pins.push_back(physics::createCircle(world, 53 + 53*h, 320, 3, b2_staticBody));
        physics::setBlockColor(pins.back(),Color(122, 226, 10));
        }

        for (int h = 0; h < 6; h++){
        pins.push_back(physics::createCircle(world, 27 + 53*h, 370, 3, b2_staticBody));
        physics::setBlockColor(pins.back(),Color(13, 224, 34));
        }

        for (int h = 0; h < 5; h++){
        pins.push_back(physics::createCircle(world, 53 + 53*h, 420, 3, b2_staticBody));
        physics::setBlockColor(pins.back(),Color(29, 226, 157));
        }

        //catcher thingys
        Block catcher;
        for (int h = 0; h < 6; h++){
        catcher = physics::createBox(world, 25 +53*h, 460, 3, 240, b2_staticBody);
        physics::setBlockColor(catcher, Color(29, 226, 157));
        }

        //floor so they stop falling forever
        physics::createBox(world, 0, 700, 320, 3, b2_staticBody);

        //creating physical ball outside of loo
        Block Ball;

//////////////////////////////////////////////////////////////////////////MAIN LOOOOOOOOOOOOOOOP///////////////////////////////////////////////////////////////
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonReleased)
            {
                click = true;
                if (playing == true || options == true) click2 = true;
            }

        }
    //drawing background
    window.draw(bg);


///////////////////////////////////////////MENU SCREEN////////////////////////////////////////////

    if (mainmenu == true)
    {
        menu.setTexture(menumain);

        //play
        if (Mouse::getPosition(window).x > 120 && Mouse::getPosition(window).x < 200 && Mouse::getPosition(window).y > 190 && Mouse::getPosition(window).y < 215)
        {
            menu.setTexture(menumainp);
            if (click == true)
            {
                splay.play();
                playing = true;
                mainmenu = false;
                options = false;
                waitwhat = false;
            }
        }
        //options
        if (Mouse::getPosition(window).x > 90 && Mouse::getPosition(window).x < 225 && Mouse::getPosition(window).y > 295 && Mouse::getPosition(window).y < 315)
        {
            menu.setTexture(menumaino);
            if (click == true)
            {
                click1.play();
                playing = false;
                mainmenu = false;
                options = true;
                waitwhat = false;
            }
        }
        //how to
        if (Mouse::getPosition(window).x > 70 && Mouse::getPosition(window).x < 245 && Mouse::getPosition(window).y > 395 && Mouse::getPosition(window).y < 415)
        {
            menu.setTexture(menumainww);
            if (click == true)
            {
                click1.play();
                playing = false;
                mainmenu = false;
                options = false;
                waitwhat = true;
                click = false;
            }
        }
    }


////////////////////////////changing color texture stuff////////////////////
    if (blueb == true)
    {
        colors.setTexture(optionsblue);
        a = 20;
        b = 172;
        c = 255;
    }
    if (cyanb == true)
    {
        colors.setTexture(optionscyan);
        a = 62;
        b = 209;
        c = 204;
    }

    if (greenb == true)
    {
        colors.setTexture(optionsgreen);
        a = 42;
        b = 224;
        c = 60;
    }

    if (orangeb == true)
    {
        colors.setTexture(optionsorange);
        a = 226;
        b = 129;
        c = 24;
    }

    if (pinkb == true)
    {
        colors.setTexture(optionspink);
        a = 239;
        b = 103;
        c = 200;
    }

    if (purpleb == true)
    {
        colors.setTexture(optionspurple);
        a = 184;
        b = 31;
        c = 226;
    }

    if (redb == true)
    {
        colors.setTexture(optionsred);
        a = 242;
        b = 31;
        c = 42;
    }

    if (yellowb == true)
    {
        colors.setTexture(optionsyellow);
        a = 255;
        b = 242;
        c = 10;
    }


////////////////////////////changing background texture stuff///////////////
    if(woodb == true)
    {
        bg.setTexture(wood);
        bgbutton.setTexture(optionswood);
    }

    if(bricksb == true)
    {
        bg.setTexture(bricks);
        bgbutton.setTexture(optionsbricks);
    }

    if(cfb == true)
    {
        bg.setTexture(cf);
        bgbutton.setTexture(optionscf);
    }

    if(electricityb == true)
    {
        bg.setTexture(electricity);
        bgbutton.setTexture(optionselectricity);
    }

    if(fireb == true)
    {
        bg.setTexture(fire);
        bgbutton.setTexture(optionsfire);
    }

    if(iceb == true)
    {
        bg.setTexture(ice);
        bgbutton.setTexture(optionsice);
    }

    if(metalb == true)
    {
        bg.setTexture(metal);
        bgbutton.setTexture(optionsmetal);
    }

    if(stoneb == true)
    {
        bg.setTexture(stone);
        bgbutton.setTexture(optionsstone);
    }

    if(waterb == true)
    {
        bg.setTexture(water);
        bgbutton.setTexture(optionswater);
    }


///////////////////////////////////////////OPTIONS SCREEN////////////////////////////////
    if (options == true)
    {

    //color button
    if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < 260 && Mouse::getPosition(window).y > 190 && Mouse::getPosition(window).y < 215)
    {

        if ( blueb == true)
        {
            if (click == true)
            {
                click02.play();
                blueb = false;
                yellowb = true;

                click = false;
            }
        }

        if ( cyanb == true)
        {
            if (click == true)
            {
                click02.play();
                cyanb = false;
                blueb = true;
            }
        }

        if ( greenb == true)
        {
            if (click == true)
            {
                click02.play();
                greenb = false;
                cyanb = true;
            }
        }

        if ( orangeb == true)
        {
            if (click == true)
            {
                click02.play();
                orangeb = false;
                greenb = true;
            }
        }

        if ( pinkb == true)
        {
            if (click == true)
            {
                click02.play();
                pinkb = false;
                orangeb = true;
            }
        }

        if ( purpleb == true)
        {
            if (click == true)
            {
                click02.play();
                purpleb = false;
                pinkb = true;
            }
        }

        if ( redb == true)
        {
            if (click == true)
            {
                click02.play();
                redb = false;
                purpleb = true;
            }
        }

        if ( yellowb == true)
        {
            if (click == true)
            {
                click02.play();
                yellowb = false;
                redb = true;
            }
        }
    }
    window.draw(colors);


    //background button
    if (Mouse::getPosition(window).x > 40 && Mouse::getPosition(window).x < 280 && Mouse::getPosition(window).y > 295 && Mouse::getPosition(window).y < 315)
    {
        if(woodb == true)
       {
           if (click2 == true)
           {
               click02.play();
               woodb = false;
               waterb = true;

               click2 = false;
           }
       }

        if(bricksb == true)
        {
            if (click2 == true)
            {
                click02.play();
                bricksb = false;
                woodb = true;
            }
        }

        if(cfb == true)
        {
            if (click2 == true)
            {
                click02.play();
                cfb = false;
                bricksb = true;
            }
        }

        if(electricityb == true)
        {
            if (click2 == true)
            {
                click02.play();
                electricityb = false;
                cfb = true;
            }
        }

        if(fireb == true)
        {
            if (click2 == true)
            {
                click02.play();
                fireb = false;
                electricityb = true;
            }
        }

        if(iceb == true)
        {
            if  (click2 == true)
            {
                click02.play();
                iceb = false;
                fireb = true;
            }
        }

        if(metalb == true)
        {
            if (click2 == true)
            {
                click02.play();
                metalb = false;
                iceb = true;
            }
        }

        if(stoneb == true)
        {
            if (click2 == true)
            {
                click02.play();
                stoneb = false;
                metalb = true;
            }
        }

        if(waterb == true)
        {
            if (click2 == true)
            {
                click02.play();
                waterb = false;
                stoneb = true;
            }
        }
    }
    window.draw(bgbutton);

        //back button
        backbtn.setTexture(optionsback);
        if (Mouse::getPosition(window).x > 120 && Mouse::getPosition(window).x < 200 && Mouse::getPosition(window).y > 395 && Mouse::getPosition(window).y < 415)
        {
            backbtn.setTexture(optionsbackbold);
            if (click == true)
            {
                click1.play();
                playing = false;
                mainmenu = true;
                options = false;
                waitwhat = false;
            }
        }
        window.draw(backbtn);
    }

    //////////////////////////////////how to screen////////////////////////////////////////////
    if (waitwhat == true)
    {
        window.draw(howto);

        backbtn.setTexture(optionsback);

        if (Mouse::getPosition(window).x > 120 && Mouse::getPosition(window).x < 200 && Mouse::getPosition(window).y > 395 && Mouse::getPosition(window).y < 415)
        {
            backbtn.setTexture(optionsbackbold);
            if (click == true)
            {
                click1.play();
                playing = false;
                mainmenu = true;
                options = false;
                waitwhat = false;
            }
        }
        window.draw(backbtn);

    }

    if (mainmenu == true)
    {
        window.draw(menu);
    }

//    if (playing == true){
//        window.draw(pointslayer);
//        if (hovering == true) window.draw(hoverball);
//        physics::displayWorld(world, window);
//    }

    ////////////////////////////////////////////PLAYING SCREEN/////////////////////////////////////////////
    if(playing == true)
    {

    physics::displayWorld(world, window);

    hoverball.setFillColor(Color(a, b, c));
    window.draw(pointslayer);
    if (hovering == true) window.draw(hoverball);

    if (hovx > 273) hovmove = -hovmove;
    if (hovx < 25) hovmove = -hovmove;

    hovx = hovx + hovmove;
    hoverball.setPosition(hovx, 20);

    if (click2 == true && hovering == true)
    {
       hovering = false;
       Ball = physics::createCircle(world, hovx, 25, 11);
       physics::setBlockColor(Ball, Color(a, b, c));
       sdrop.play();
    }


    if (hovering == false)
    {

    if (physics::checkCollision(Ball) == true && physics::getPosition(Ball).y < 480) hit.play();

    if (physics::getPosition(Ball).x < 25 && physics::getPosition(Ball).y > 480)
        score = 10;

    if (physics::getPosition(Ball).x > 25 && physics::getPosition(Ball).x < 78 && physics::getPosition(Ball).y > 480)
        score = 5;

    if (physics::getPosition(Ball).x > 78 && physics::getPosition(Ball).x < 131 && physics::getPosition(Ball).y > 480)
        score = 3;

    if (physics::getPosition(Ball).x > 131 && physics::getPosition(Ball).x < 184 && physics::getPosition(Ball).y > 480)
        score = 1;

    if (physics::getPosition(Ball).x > 184 && physics::getPosition(Ball).x < 237 && physics::getPosition(Ball).y > 480)
        score = 3;

    if (physics::getPosition(Ball).x > 237 && physics::getPosition(Ball).x < 290 && physics::getPosition(Ball).y > 480)
        score = 5;

    if (physics::getPosition(Ball).x > 290 && physics::getPosition(Ball).y > 480)
        score = 10;
    }

////////////////////////////////////////Returning to Menu///////////////////////////////////
    if (score > 0)
    {
        if (score == 1)
        {
            scorez.setTexture(onepoint);
        }
        if (score == 3)
        {
            scorez.setTexture(threepoint);
        }
        if (score == 5)
        {
            scorez.setTexture(fivepoints);
        }
        if (score == 10)
        {
            scorez.setTexture(tenpoints);
        }

        if (Mouse::getPosition(window).x > 30 && Mouse::getPosition(window).x < 290 && Mouse::getPosition(window).y > 380 && Mouse::getPosition(window).y < 410)
        {
            restart.setTexture(restartbtnbold);
            if (click == true)
            {
                click1.play();
                playing = false;
                mainmenu = true;
                options = false;
                waitwhat = false;
                hovering = true;
                score = 0;
            }
        }

        else restart.setTexture(restartbtn);
        window.draw(scorez);
        window.draw(restart);
    }

    }
        //tests
        if (mainmenu == true) cout<<"Menu"<<endl;
        if (options == true) cout<<"Options"<<endl;
        if (playing == true) cout<<score<<endl;

        click = false;
        click2 = false;
        window.display();
        window.clear();
    }

    return 0;
}
