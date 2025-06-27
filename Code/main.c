#include<stdio.h>
// Including the headers I saw in a video, don't know what all of their usecases are yet
#include<stdlib.h> 
#include<string.h>
#include<ctype.h>
#include "functions.h"  // Including the header where the functions are declared


int main() 
{
    ClearScreen(); // clears screen
    int GameOn = 1, area = 0, choice = 0; // Game loop checker, area checker, and choice checker
    int PlayerHealthMax = 3, PlayerHealth = PlayerHealthMax, PlayerPower = 1; // Player stats
    int *HealthPointer = &PlayerHealth; // Health in pointer to change it freely in functions

    int MisWin = 0; // check to see if you have met Misdirection Man
    int BozoWin = 0; // See if you won again big bozo

    int mean = 0; // variable to check if you heckled Dough's show

    int InTheKnowPath = 0; // Will show different text of path if player asks about the paths
    int WizTalk = 0; // shows if you talked to wiz
    int ComedyShowdown = 0; // initator for a showdown battle with Dough
    int Wrong = 0; // to track if player made any mistake in Wiz's puzzle
    int Short = 0; // to see if the player did not want to listen to the story Wiz had to tell

    int encHealth, encPower; // Variables for encouter health and power if i want it to vary

    int tracker; // This variable is for incase i want to track multiple instances of something in a choice

    // These two are for encounters in different areas, the numbers in the arrays are the area.
    // When the player faces an encounter in an area, the area is removed
    int areaEncounter[] = {2, 2, 4, 5, 7};
    int sizeEnc = sizeof(areaEncounter) / sizeof(areaEncounter[0]);


    int GreenEnc = 0; // See how many times you have interacted with Green
                      // Really only used to check if you've encountered once before

    // These are for checking if the player has the respective orbs, and if they have inserted it into the door
    // Plus seeing if the door has been opened
    int Heart = 0, InsertH = 0, Mind = 0, InsertM = 0, Body = 0, InsertB = 0, OrbCount = 0, Open = 0;
    
    // Player name dynamically allocated
    char *PlayerName;
    PlayerName = (char*) calloc(30, sizeof(char));

    // Game will run forever until GameOn is false
    while (GameOn){
        // seperated into different areas (sections), will always start at 0 but choices lead to different areas

        // Naming menu
        if (area == 0){
            // loops until confirmation
            do{
                printf("What is your name?\n");
                InputString(PlayerName, 30);
                printf("\nIs %s correct?\n\n1. Yes\n2. No\n", PlayerName);
                choice = ChoiceInput(2);
            } while (choice == 2);
            area = 1;
        }
        // Displays entrance text, and allows user to get used to entering options
        else if(area == 1){
            
            printf("Welcome %s!\n\n", PlayerName);
            PrintText("area.txt", "INTRO");
            choice= ChoiceInput(1);
            area = 2;
        }

        // Green Goblin area and intersection between other areas
        else if (area == 2){
            //  if you havent encountered green
            if (GreenEnc == 0){
                PrintText("area.txt", "CAVEFIRST");
                choice = ChoiceInput(1);
                Sleeps(2000);
                ClearScreen();
                // first monster encounter
                if (RemoveValue(areaEncounter, area, &sizeEnc)){
                    printf("But the cave is not that inviting it seems. An angry slime blocks your path!\n\n1. Fight it\n");
                    choice = ChoiceInput(1);
                    BattleMode(HealthPointer, 2, PlayerPower, 1, PlayerName, "Weak Slime");
                    printf("That was not a very difficult fight...\n");
                    LevelUp(&PlayerHealthMax);
                    Heal(PlayerHealthMax, HealthPointer);
                    Sleeps(5000);
                    ClearScreen();
                }
                // printing text from area.txt and getting players choices
                PrintText("area.txt", "CAVETWO");
                choice = ChoiceInput(1);
                Sleeps(2000);
                ClearScreen();
                PrintText("area.txt", "GREENONE");
                choice = ChoiceInput(2);
                tracker = 1;
                PrintText("area.txt", "GREENTWO");
                // player can ask all the questions given here
                do{
                choice = ChoiceInput(6);
                ClearScreen();
                if (choice == 1){
                    printf("Green: I am not sure. But Miss Wiz says whatever inside will free us.\nGreen: And that the only way to open it is to obtain all three orbs. Whatever those are.\n\n1. Continue\n");
                }
                else if (choice == 2){
                    printf("Green: That's what they all say! By the end of the day, they just join the circus\n\nYou hear faint circus music coming from the path next to the shop.\n\n1. Continue\n");
                }
                else if (choice == 3){
                    // tracker variable tracks green goblin comparisions here
                    switch(tracker){
                    case 1: printf("Angry Green: NO NOT LIKE THE SPIDER-MAN VILLAIN. IT IS AN ORIGINAL NAME!\n\n1. Continue\n"); break;
                    case 2: printf("Angry Green: I DON'T EVEN KNOW WHO THAT IS! EVERYONE IN THE CAVE ASKS ME THAT!\n\n1. Continue\n"); break;
                    default: printf("Fed-Up Green: STOP ASKING ME THAT!\n\n1. Continue\n"); break;
                    }
                    tracker++;
                }
                else if (choice == 4){
                    printf("Green: Yes! This is my humble shop, \"The Greenest Shop\"! I really like that naming scheme.\nGreen: I sell all things green. At the moment, that's just green hair dye.\n\nGreen: But you don't have any of our currency down here. Come back later if you want to dye your hair!\n\n1. Continue\n");
                }
                else if (choice == 5){
                    printf("Green: Well the path right next to me goes to Big Bozo's Circus.\nGreen: He has a lot of \"animals\". I don't think it's very ethical. But it's entertaining!\n");
                    printf("Green: The path across us, splits into two other ways. The left one goes to Dough's Standup Show. I guess being stuck down here really led us to the entertainment industry.\nGreen: He is not very good though. The right path goes to Miss Wiz's puzzle room. You're gonna have to solve some puzzles if you want to meet her.\n\n1. Continue\n");
                    InTheKnowPath = 1; // small text qof later
                }
                (choice != 6) ? choice = ChoiceInput(1) : printf("");
                ClearScreen();
                (choice != 6) ? PrintText("area.txt", "GREENTHREE") : printf("");
                }while (choice != 6);
                printf("Green: You're leaving? Well, you can come back to get some hair dye!\n");

                GreenEnc++;
            }
            // When you finish the quest and before the completion of the game, green dialouge
            else if(OrbCount == 3){
                PrintText("area.txt", "GREEND");
                choice = ChoiceInput(4);
                if (choice == 1){
                    printf("Green: I know you can do it! Make that guy dye! Get it? Nyah nyah nyah!\n\n");
                }
                else if (choice == 2){
                    printf("Sobbing Green: This is the best day of my life. I WILL SAVE THE BEST FOR YOU!\n\n");
                }
                else if (choice == 3){
                    printf("You can always count on The Green Goblin!\n\n");
                }
                else if (choice == 4){
                    printf("Green: Oh");
                    Akward();
                    printf("\nGreen: Sorry");
                    Akward();
                    printf("\nGreen: Nevermind that!\n\n");
                }
                Sleeps(2000);
                printf("Green: Goodluck %s!!!\n\n1. Go to the door.\n", PlayerName);
                choice = ChoiceInput(1);
                area = 3;

            }
            // second time meeting green
            else{
                // another encounter
                if (RemoveValue(areaEncounter, area, &sizeEnc)){
                    printf("As you head back to the Greenest Shop, your path is blocked by a furious slime!\nDecent Slime: You hurt my lil bro earlier bro. I can not let that slide bro.\nDecent Slime: Square up bro.\n\n1. Fight it\n");
                    choice = ChoiceInput(1);

                    BattleMode(HealthPointer, 3, PlayerPower, 1, PlayerName, "Decent Slime");
                    printf("This cave seems really slimy...\n\n");
                    LevelUp(&PlayerHealthMax);
                    Heal(PlayerHealthMax, HealthPointer);
                    Sleeps(2000);
                    ClearScreen();
                }
                // tracker here tracks which encounter you're one
                tracker = 0;
                if(OrbCount>0){
                    printf("Green: Looks like you got some orbs! I'm starting to believe in you. Need any help?\n\n");
                }
                else{
                    if (GreenEnc > 2){
                        printf("Green: Hey %s! Welcome back to my humble green shop! How has the cave been treating you?\n\n", PlayerName);
                        tracker = 1;
                    }
                    else{
                        printf("Green: You were just here...\n\n");
                        tracker = 2; // if you just went and came back and no where else
                    }
                }
                
                do{
                GreenEnc++;
                PrintText("area.txt", "GREENRECURRING");
                choice = ChoiceInput(8);
                ClearScreen();
                if (choice == 1){
                    switch(tracker){
                        case 0: printf("Green: You could always use some green hair to save the day, %s.\n\n1. Continue\n", PlayerName); break;
                        case 1: printf("Green: That's grrreat. You know what else starts with 'gr'? GREEN dye, get some green dye.\n\n1. Continue\n"); break;
                        case 2: printf("Green: ...\n\n1. Continue\n"); break;
                    }
                }
                else if (choice == 2){
                    printf("Green: Me? Well I had just started my business in the Radeshian city!\nGreen: The city guards told me I would have better business in this cave.\nGreen: I think they were pranking me...\nGreen: But I'm the only shop stationed here! So I am basically a monopoly nyah nyah nyah nyah!\n\n1. Continue\n");
                }
                else if (choice == 3){
                    printf("Green: Miss Wiz? She's a wizard. She has a very short, wears a very big cloak, and she has a magnificent beard\nGreen: She knows more about getting out of here than anyone, but she won't do anything.\nGreen: Apparently because she does not think anyone who has come down here is worthy enough! She's still chill though.\n\n1. Continue\n");
                }
                else if (choice == 4){
                    printf("Green: Dough? He's a weird guy. He's very lanky, light purple skin, and two little horns on his head; also purple.\nGreen: He came to this cave to write some material for his show. And when he got stuck here, he just shifted his show here.\nGreen: I don't know how he even booked anything outside, because he is terrible.\nGreen: Even with terrible jokes and an unimpressed audience, he moves on. He has heart atleast.\n\n1. Continue\n");
                }
                else if (choice == 5){
                    printf("Green: Big Bozo? That guy is insane! He is not big, but he is a bozo. Clown makeup on and a big red nose.\nHe used to have big circus outside I guess. Then him and his crew stationed here for the night. And well the rest of his nights.\nGreen: He throws his circus shows here now. But since he's missing his biggest attraction, the circus animals.\nGreen: He dresses his crew as animals... Yeah.\n\n1. Continue\n");
                }
                else if (choice == 6){
                    printf("Green: I plan to sell out all my dye by the end of the year! So far I've sold 1%% of it.\n\nYou notice 360 notches scratched behind him. He better hurry up.\n\nGreen: Would you like some??\n\n1. Ignore\n");
                }
                else if(choice == 8){
                    printf("Green: Secret option? Eight? What? You can buy some of my dye if that's what you're asking.\n\n%s: No.\n\nGreen: :(\n\n1. Continue\n", PlayerName);
                }
                (choice != 7) ? choice = ChoiceInput(1) : printf("");
                ClearScreen();
                
                }while (choice != 7);


                printf("Green: Have fun meanderning around the cave!\n\n");
            }
            PrintText("area.txt", "CAVETHREE");
            // option to explore cave
            printf("1. Go to door\n2. Go to Green\n3. Go to the left path\n4. Go to the right path\n\n");
            choice = ChoiceInput(4);
            if (choice == 1){
                area = 3; // ending of game
            }
            else if (choice == 2){
                area = 2; // back to green
            }
            else if (choice ==3){
                area = 4; // dough and miss wiz
            }
            else{
                area = 7; // big bozo
            }
        }

        // door area
        // checks for you orbs
        // you can place them if you have them
        // but if you have all the orbs youre forced into the final battle
        else if (area == 3){
            tracker = 0;
            PrintText("area.txt", "DOOR");
            if (OrbCount == 0){
                printf("1. exit\n");
                ChoiceInput(1);
                area = 2;
            }
            else if(OrbCount > 0){
                printf("1. Place orbs into slots\n");
                choice = ChoiceInput(1);
                printf("\n");
                if (Heart && InsertH != 1){
                    printf("The Heart Orb\n");
                    InsertH = 1;
                }
                if (Mind && InsertM != 1){
                    printf("The Mind Orb\n");
                    InsertM = 1;
                }
                if (Body && InsertB != 1){
                    printf("The Body Orb\n");
                    InsertB = 1;
                }
                printf("Placed into the door");
                Akward();
                printf("\n");
                if (InsertM && InsertB && InsertH){
                    Open = 1;
                }
            }
            Sleeps(2000);
            if(Open){
                printf("The door opens");
                Akward();
                printf("\n\n1. Enter\n");
                choice = ChoiceInput(1);
                area = 13;
            }
            else if (OrbCount>0 && Open != 1){
                printf("1. exit\n");
                ChoiceInput(1);
                area = 2;
            }
        }
        

        // left path that leads to dough or miss wiz
        else if (area == 4){
            PrintText("area.txt", "INTERSECTION");
            choice = ChoiceInput(1);
            printf("\n\n");
            // first time you go to this intersection you meet misdirection man, who just spews nonsense
            if (MisWin != 1){
                PrintText("area.txt", "MISSMAN");
                choice = ChoiceInput(1);
                printf("???: Hello %sie.\nMisdirection Man: I am Misdirection Man. I heard your name from your conversation with Green.\nMisdirection Man: You're gonna wanna turn around to meet Miss Whiz. Don't let my name fool you.\n\n1. Ok??\n2. No\n", PlayerName);
                choice = ChoiceInput(2);
                printf("Misdirection Man fades into the text file");
                Sleeps(200);
                Akward();
                printf("\n\n");
                MisWin = 1;
                PrintText("area.txt", "INTERSECTION");
                choice = ChoiceInput(1);
                Sleeps(100);
                ClearScreen();
            }
            // second time you face purple lobster and gain a powerup
            else if(RemoveValue(areaEncounter, area, &sizeEnc)){
                printf("But somethings standing between the intersection! It's not the misdirection man");
                Sleeps(100);
                Akward();
                printf("\nBut a purple lobster?\n\nPurple Lobster: Don't mess around my turf! *Clank Clank*\nIt clicks it pinchers\n\n1. FIght it\n");
                choice = ChoiceInput(1);
                BattleMode(HealthPointer, 2, PlayerPower, 2, PlayerName, "Purple Lobster");
                printf("The Purple Lobster drops his purple pincher. Seems like they were add ons...\nYou pick up the pinchers. Feels like you can attack a little stronger.\n\n1. Continue\n");
                ChoiceInput(1);
                LevelUp(&PlayerHealthMax);
                Heal(PlayerHealthMax, HealthPointer);
                PlayerPower++;
                Sleeps(2000);
                ClearScreen();
                PrintText("area.txt", "INTERSECTION");
                choice = ChoiceInput(1);
                Sleeps(100);
                ClearScreen();
            }
            // the small qof of talking to green
            (InTheKnowPath) ? printf("\n\n1. Go left to Dough\n2. Go right to Miss Wiz\n3. Go back to Green\n") : printf("\n\n1. Go left\n2. Go right\n3. Go back\n");
            choice = ChoiceInput(3);
            if (choice == 1){
                area = 5;
            }
            else if (choice == 2){
                area = 6;
            }
            else if (choice == 3){
                area = 2;
            }
            

        }

        // left, doughs standup
        else if (area == 5){
            // if you got the orb from Dough, then everyone has left the show
            if (Heart){
                printf("The comedy show is empty. Only a neon sign:\n%s's Comedy Show\n\n", PlayerName);
                if(RemoveValue(areaEncounter, area, &sizeEnc)){
                    printf("Except for a lone Red Scorpion on stage.\n\nRed Scorpion: Wanna hear a joke?\n\nIt jumps toward you\n\n1. Fight it\n");
                    ChoiceInput(1);
                    BattleMode(HealthPointer, PlayerHealthMax-1, PlayerPower, 2, PlayerName, "Red Scorpion");
                    printf("That was not very funny\n");
                    LevelUp(&PlayerHealthMax);
                    Heal(PlayerHealthMax, HealthPointer);
                    Sleeps(5000);
                    ClearScreen();
                    printf("The comedy show is empty. Only a neon sign:\n%s's Comedy Show\n\n", PlayerName);
                }
                printf("1. Exit\n");
                ChoiceInput(1);
                area = 4;
            }
            else{       
                
                encHealth = 3;
                PrintText("area.txt", "COMEDYCLUB");
                choice = ChoiceInput(4);
                ClearScreen();
                tracker = 1;
                if (choice == 1){
                    // loop till you laugh at dough
                    do{
                        // tracker makes it so that Dough cycles through the same three jokes
                        switch(tracker){
                            case 1: PrintText("area.txt", "JOKEONE"); break;
                            case 2: PrintText("area.txt", "JOKETWO"); break;
                            case 3: PrintText("area.txt", "JOKETHREE"); break;
                            default: printf("Stevie bites you\n"); break;
                        }
                        printf("1. Boo\n2. Heckle\n3.Laugh\n");
                        choice = ChoiceInput(3);
                        if (choice == 1){
                            printf("Dough: Yeah keep booing. There's nothing better here. Go to Bozo's freak show and you'll see!\n\nDough stifles a tear\n\n1. Continue\n");
                        }
                        else if (choice == 2){
                            mean = 1; // if youre mean he will comment on it once in the future again
                            switch(tracker){
                            case 1: printf("%s: This is the worst thing since 9/11, Derkwad.\n\n", PlayerName); break;
                            case 2: printf("%s: Who booked this guy? Guy seems like a real Derkwad.\n\n", PlayerName);; break;
                            case 3: printf("%s: Get off stage, Derkwad.\n\n", PlayerName);; break;
                            default: printf("%s bites you\n", PlayerName); break;
                            }
                            
                            printf("Dough is stunned in silence. You can feel the audience staring at you.\n\nIn-Tears Dough: DERKWAD!? THAT IS THE MOST HURTFUL THING I HAVE EVER HEARD\n\nDough lets out a sob. Even if the audience is not very impressed with Dough, they certaintly don't like you.\n\nNo-Longer-Sobbing Dough: I'm going back to my jokes.\nReady-To-Joke Dough: But know that we will all think of you as a terrible person. YOU the player, grrrraaaaaaa\n\n1. Reflect upon yourself");
                        }
                        else if(choice == 3){
                            printf("Dough looks at you in shock. The audience members give a loud gasp.\n\nTeary-Eyed Dough: Y-y-you liked my joke?!?!\n%s: Yes\nHappy Dough: This has never happened before", PlayerName);
                            Akward();
                            printf("\n");
                            if (mean){
                                printf("Dough: Even though you did not like my joke earlier, there is still whimsy in your heart.\n");
                            }
                            printf("Dough: You must be a special breed! A funny one! Come upstage, Let's work together!\n\n1. Go upstage\n");
                        }
                        (choice != 3) ? choice = ChoiceInput(1) : ChoiceInput(1);
                        
                        printf("\n\nHis donut seems to have regained all its parts");
                        Akward();
                        Sleeps(1500);
                        ClearScreen();
                        tracker++;
                        // overflows the tracker variable
                        if (tracker > 3){
                            tracker = 1;
                        }

                    } while (choice != 3);
                    choice = 5; // this path always leads  to a comedy showdown, going to 5 because the leadup text is different
                    
                }
                else if (choice == 2){
                    printf("Guy who looks like a rolling pin: Place is busy bud.\n\n1. Leave\n");
                    choice = ChoiceInput(1);
                    ClearScreen();
                }
                else if(choice == 3){
                    // this one either leads to comedy showdown or an actual showdown
                    PrintText("area.txt", "STAGECONFUSED");
                    choice = ChoiceInput(2);
                    if (choice == 1){
                        ComedyShowdown = 1;
                    }
                    else{
                        printf("\n\nDough: Take my donut? Why?\n\n%s: ", PlayerName);
                        // if you have talked to wiz, you can use the knowledge you gained from her
                        (WizTalk) ? printf("That's a very valuable orb.") : printf("It seems to be your only possession.");
                        printf("\n\nDough: What? That's a very odd reason. This was given to me by Miss Wiz.\nDough: She said to only give it those with whimsy!\n\n1. \"I'll tell you funny jokes\"\n2. Fight him\n");
                        choice = ChoiceInput(2);
                        if (choice == 1){
                            ComedyShowdown = 1;
                        }
                        else if (choice == 2){
                            BattleMode(HealthPointer, encHealth, PlayerPower, 1, PlayerName, "Dough");
                            printf("Dough falls on the stage floor.\n");
                            LevelUp(&PlayerHealthMax);
                            Heal(PlayerHealthMax, HealthPointer);
                            Sleeps(2000);
                            ClearScreen();
                            PrintText("area.txt", "DOUGHWIN");
                            ChoiceInput(1);
                            Heart = 1;
                            OrbCount++;
                            area = 4;
                        }

                    }
                }
                else if(choice == 4){
                    area = 4;
                }
                if (choice == 5){
                    printf("Dough: I have never had anyone on stage with me. There's something I want to do.\n\nDough becomes serious, he throws his donut in the air and catches it when it comes back down.\n");
                    ComedyShowdown = 1;
                }

                if (ComedyShowdown){
                    // The comedy showdown is displayed like a battle but you pick between jokes
                    // every joke you do deals damage to dough, cause he is not very funny
                    printf("\nCompetitive Dough: Alright I guess that calls");
                    Sleeps(300);
                    Akward();
                    printf(" for a");
                    Sleeps(300);
                    Akward();
                    printf("COMEDY SHOWDOWN!\n\n1. Continue\n");
                    ChoiceInput(1);
                    Akward();
                    ClearScreen();
                    printf("Comedy showdown between %s and Dough!", PlayerName);
                    Sleeps(2000);
                    
                    while (encHealth>0){
                        BattleScreen(PlayerHealth, encHealth, PlayerName, "Dough");
                        if (tracker == 1){
                            PrintText("area.txt", "PUN");
                            choice = ChoiceInput(3);
                            printf("\n\nThe audience giggles. Seems anything subpar will impress them.\n\n");
                            (choice != 3) ? printf("Flustered Dough: That was not very punny."): printf("Dough: That was just a threat...");
                            printf("\n\n1. Continue\n");
                            ChoiceInput(1);
                        }
                        else if (tracker == 2){
                            PrintText("area.txt", "CROWDWORK");
                            choice = ChoiceInput(3);
                            printf("\n\nThe rolling pin giggles.\n\n");
                            (choice != 3) ? printf("Flustered Dough: That's the joke that got you rolling?"): printf("Dough: That was just mean...");
                            printf("\n\n1. Continue\n");
                            ChoiceInput(1);
                            
                        }
                        else if (tracker == 3){
                            PrintText("area.txt", "SLAPSTICK");
                            choice = ChoiceInput(1);
                            printf("\n\nEverbody laughs.\n\nDough: What!\n\n1. \"%s: That's just how it goes\"\n", PlayerName);
                            ChoiceInput(1);
                            
                        }
                        encHealth--;
                        tracker++;
                        Sleeps(200);
                        ClearScreen();
                    }
                    PrintText("area.txt", "WINCOMEDY");
                    ChoiceInput(1);
                    Heart = 1;
                    OrbCount++;
                    printf("\n\n%s: You ate this thing?\n\nDough: Yeah, it's a magical donut.\n\n1. Exit\n", PlayerName);
                    ChoiceInput(1);
                    area = 4;
                }
                if (Heart){
                    // when you get an orb you get a boost in power
                    PlayerPower++;
                }
            }
        
            
        }
        
        // Miss Wiz puzzle area
        else if (area == 6){
            // here the player is asked 3 questions, and if they get one wrong they will have to fight a create to make up for it
            PrintText("area.txt", "PUZZLEROOM");
            ChoiceInput(1);
            Sleeps(200);
            ClearScreen();
            PrintText("area.txt", "QUESONE");
            choice = ChoiceInput(4);
            if (choice == 4){
                printf("\n\nCorrect! Congratulations, move on to the next room...\n\n1. Continue\n");
                
            }
            else{
                Wrong = 1;
                printf("\n\nWrong! Every month has 28 days! Don't pee your pants, because to move to the next room you'll have to defeat...\n\nYou hear a hissing noise behind you.\nYou turn to see a Pink Snake lunging at you.\n\n1. Fight it\n");
                ChoiceInput(1);
                Sleeps(200);
                BattleMode(HealthPointer, 4, PlayerPower, 1, PlayerName, "Pink Snake");
                LevelUp(&PlayerHealthMax);
                printf("\nAfter defeating the snake, the door opens.\n\n1. Go inside\n");
                Heal(PlayerHealthMax, HealthPointer);
            }
            ChoiceInput(1);
            Sleeps(200);
            ClearScreen();

            PrintText("area.txt", "QUESTWO");
            choice = ChoiceInput(3);
            if (choice == 2){
                printf("\n\nCorrect! Congratulations, move on to the next room...\n\n1. Continue\n");
            
            }
            else{
                Wrong = 1;
                printf("\n\nWrong! It is important to know aspects of literature! Don't pee your pants, because to move to the next room you'll have to defeat...\n\nYou hear a snapping noise behind you.\nYou turn to see a Blue Crab lunging at you.\n\n1. Fight it\n");
                ChoiceInput(1);
                Sleeps(200);
                BattleMode(HealthPointer, 2, PlayerPower, 2, PlayerName, "Blue Crab");
                LevelUp(&PlayerHealthMax);
                printf("\nAfter defeating the crab, the door opens.\n\n1. Go inside\n");
                Heal(PlayerHealthMax, HealthPointer);
            }
            ChoiceInput(1);
            Sleeps(200);
            ClearScreen();

            PrintText("area.txt", "QUESTHREE");
            printf("4. %s\n", PlayerName);
            choice = ChoiceInput(4);
            if (choice == 4){
                printf("\n\nIt is important to be honest, move on to the next room...\n\n1. Continue\n");
                
            }
            else{
                Wrong = 1;
                printf("\n\nWrong! You should learn to be honest! Don't pee your pants, because to move to the next room you'll have to defeat...\n\nYou hear a growling noise behind you.\nYou turn to see a Orange Bear lunging at you.\n\n1. Fight it\n");
                ChoiceInput(1);
                Sleeps(200);
                BattleMode(HealthPointer, 2, PlayerPower, 2, PlayerName, "Orange Bear");
                LevelUp(&PlayerHealthMax);
                printf("\nAfter defeating the bear, the door opens.\n\n1. Go inside\n");
                Heal(PlayerHealthMax, HealthPointer);
            }
            ChoiceInput(1);
            Sleeps(200);
            ClearScreen();
            area = 8;
        }

        // Bif Bozo circus area, very rushed
        else if (area == 7){
            // one encounter on the way
            if (RemoveValue(areaEncounter, area, &sizeEnc)){
                printf("Following the circus noise, you are stopped by a clown dog made of ballons. It makes a rubber noise.\n\n1. Fight it\n");
                ChoiceInput(1);
                BattleMode(HealthPointer, 4, PlayerPower, 1, PlayerName, "Clown Dog");
                LevelUp(&PlayerHealthMax);
                Heal(PlayerHealthMax, HealthPointer);
                Sleeps(500);
                ClearScreen();
            }
            // And big bozo fight as soon as you enter
            PrintText("area.txt", "CIRCUS");
            ChoiceInput(1);
            BozoWin = BattleMode(HealthPointer, 8, PlayerPower, 2, PlayerName, "Big Bozo");
            if (BozoWin){
                printf("You knock big bozo to the ground. You notice an orb sticking out of his shirt.\n\nYou recieved the Body orb!\n\n1. Go back\n");
                Body = 1;
                OrbCount++;
                PlayerPower++;
            }
            else{
                printf("Come back to Big Bozo when youre stronger!\n\nYou scurry away to the previous area.\n\n1. Continue\n");
                Heal(PlayerHealthMax, HealthPointer);
            }
            // the only area with a lose screen
            ChoiceInput(1);
            area = 2;
        }

        // Meeting Miss Wiz
        else if (area == 8){
            WizTalk = 1;
            PrintText("area.txt", "WIZROOM");
            choice = ChoiceInput(3);
            Sleeps(200);
            ClearScreen();
            if (choice == 1){
                printf("Wiz: I'm just an old wizard, but people call me Miss Wiz\nWiz: Because my name is Wiz.\nWiz: And an old woman\n\n1. Continue\n");
            }
            else if(choice == 2){
                printf("Wiz: My name is Wiz and this is my humble study.\nWiz: After meeting a lot of the residents here, I concluded that I would only help those who could.\nWiz: Such as yourself\n\n1. Continue\n");
            }
            else if (choice == 3){
                printf("???: With all bets in, it is to say you are the only one who has made it to this room.\n\n%s: Really? ", PlayerName);
                (Wrong) ? printf("The questions did not seem that hard.\n%s: And the fights were not that difficult...", PlayerName) : printf("The questions were so easy.");
                printf("\n\n???: Well the people who get stuck down here are not very bright\nWiz: But never mind that, the name is Wiz.\n\n1. Continue\n");
            }
            ChoiceInput(1);
            Sleeps(200);
            ClearScreen();
            printf("Wiz: The cave as you know traps the people who enter. There's more to this than meets the eye.\nWiz: Would you care to listen to this old woman's tale?\n\n1. Yes\n2. No\n");
            choice = ChoiceInput(2);
            if (choice == 1){
                Sleeps(200);
                ClearScreen();
                printf("Wiz: A long time ago");
                Akward();
                printf("\n");
                PrintText("area.txt", "STORY");
            }
            else if (choice == 2){
                Short = 1; // keeps track that you did not want to hear this
                Sleeps(200);
                printf("Wiz: Oh you don't want to?\nWiz: Well, the thing is, I feel I need to tell this story whether you want to hear it or not.\nWiz: I'll tell it slightly faster just for you though.\n\n1. Continue\n");
                ChoiceInput(1);
                Sleeps(200);
                ClearScreen();
                printf("Wiz: A long time ago");
                Akward();
                printf("\n");
                PrintText("area.txt", "SHORT");
            }

            Sleeps(15000);
            printf("1. Continue\n");
            ChoiceInput(1);
            Sleeps(1000);
            ClearScreen();
            printf("Wiz: Thank you for listening to my story");
            (Short) ? printf(" even though you did not want to.") : printf(".");
            printf("\nWiz: With that said, what you need to do is defeat that dragon in a thumb wrestling match.\nWiz: Just be calm and quiet and you'll win.\nWiz: You'll need this to get to her.\n\nMiss Wiz hands you an orb.\n\nRecieved the Mind Orb!\n\nWiz: With three of the orbs, you will be able to challenge Thumbaria.\n\n1. Continue\n");
            Mind = 1;
            OrbCount++;
            PlayerPower++;
            ChoiceInput(1);
            Sleeps(200);
            ClearScreen();
            do{
                printf("Wiz: Anything you want to know, I am here.\n1. \"Thumb Wrestling?\"\n2. About orb locations\n3. \"Beard?\"\n4. exit\n");
                choice = ChoiceInput(4);
                ClearScreen();
                if (choice == 1){
                    printf("Wiz: Yes, it is a very sacred sport among the dragons.\nWiz: To beat Thumbaria, you just need to be smart and calm. Which you can be.\n1. Continue\n");
                }
                else if (choice == 2){
                    if(Heart){
                        printf("Wiz: Well you have already found the heart orb from Dough.\n");
                    }
                    else{
                        printf("Wiz: You can find the heart orb at Dough's Comedy Show.\nWiz: I gave it to him to give to someone with heart and whimsy.\nWiz: Show him you have that.\n");
                    }
                    if (Body){
                        printf("Wiz: You have already found the body orb from Bozo so no need to elaborate on that.\n");
                    }
                    else{
                        printf("Wiz: You can find the body orb at Bozo's Circus.\nWiz I gave it to him to give to someone with a balance and dexterity.\nWiz: Show him you have that.\n");
                    }
                    printf("\n1.Continue\n");
                }
                else if (choice == 3){
                    printf("Wiz: My beautiful beard? What about it? I have grown it for many millenia.\n\n1. Continue\n");
                }
                else if (choice == 4){
                    printf("Goodluck on your quest %s!\n\n1. Continue\n", PlayerName);
                    area = 4;
                }
                ChoiceInput(1);

            } while (choice != 4);

        }
        else if(area == 13){

            // scripted battle with Thumbaria

            PrintText("area.txt", "ROOM");
            printf("1. \"%s, and be prepared to be thumbed!\"\n", PlayerName);
            ChoiceInput(1);
            Sleeps(500);
            ClearScreen();
            PrintText("area.txt", "BEFOREBATTLE");

            // if you did not want to listen you say it haha
            (Short) ? printf("%s: Someone might have told me about you earlier but I wasn't really listening.\n\n", PlayerName) : printf("%s: That is not what I heard.\n\n", PlayerName);
            printf("Thumbaria: It matters not what you have been told, let us begin!\n\n1. One, two, three, four, I declare a thumb war\n");
            ChoiceInput(1);

            // Montage of your friends
            Sleeps(2000);
            Akward();
            Sleeps(500);
            Akward();
            ClearScreen();
            printf("Your thumbs are locked, tense, and trembling. You try to remember what Wiz told you");
            Akward();
            printf("\n\nWiz: You need to be calm and smart!\n\n%s: It's like I can hear her right now", PlayerName);
            Sleeps(1000);
            Akward();
            printf("\n\nWiz: Because I am here!\n\nYou see her in the corner of your eye cheering you on. But it isn't just her. It is everyone!\n\n1. Turn Around\n");
            ChoiceInput(1);
            Sleeps(1000);
            ClearScreen();

            // classic rpg ending of all the character getting together
            printf("\nWiz: \"Unleash that mind magic, you've got this!\"\n");
            Sleeps(500);
            printf("Dough: \"Stay soft, stay strong-you're rising beautifully!\"\n");
            Sleeps(500);
            printf("Pink Snake: \"Slither with style! You're unstoppable!\"\n");
            Sleeps(500);
            printf("Red Scorpion: \"Strike true, fierce one-this is your moment!\"\n");
            Sleeps(500);
            printf("Green: \"Grow bold-you're brighter than you think!\"\n");
            Sleeps(500);
            printf("Orange Bear: \"Roar like you mean it! You've got bear power!\"\n");
            Sleeps(500);
            printf("Clown Dog: \"Bark with joy, Clown Dog-this is your circus now!\"\n");
            Sleeps(500);
            printf("Weak Slime: \"Even the smallest slime can shine-go!\"\n");
            Sleeps(500);
            printf("Bozo: \"They'll laugh now-but you'll win the last round!\"\n");
            Sleeps(500);
            printf("Purple Lobster: \"Snap with flair, Lobster-you're built for this!\"\n");
            Sleeps(500);
            printf("Man Who Looks Like a Rolling Pin: \"Roll on, mysterious man-you are oddly perfect!\"\n");
            Sleeps(500);
            printf("Blue Crab: \"Side-step and surprise-your claws know the rhythm!\"\n");
            Sleeps(500);
            printf("Decent Slime: \"Hold the line-your slime's got what it takes!\"\n");
            Sleeps(500);
            printf("Misdirection Man: \"Left, right-where'd you go? You clever trickster!\"\n\n\n");
            Akward();
            printf("\n%s: Wow guys", PlayerName);
            Akward();
            // You don't neccessarily fight them all 
            printf("I did not even meet some of you guys but still. Thanks. I'll do it now.\n\n1. Ultimate Finisher: Thumbs Down\n");
            ChoiceInput(1);
            Sleeps(1000);
            ClearScreen();
            printf("THUMBS DOWN\n\nWith a sudden, loud shift, you pin the dragon's thumb down.\n\nThumbaria: No, this can't be!!\n\n%s: Countdown...\n", PlayerName);
            for (int i = 10; i >0; i--){
                printf("%s: %d\n\n", PlayerName, i);
                Sleeps(1000);
            }
            printf("Everyone: ZERO!\n\n");
            printf("And with that, %s defeated Thumbaria in a thumb wrestling match. With Thumbaria's mighty thumb finally pinned, her rage has settled like ash in a quiet cave. \nThe curse is lifted. The lost are free. And the valleys of Radeshia echo once again with laughter, not fear.\n\n1. Continue\n", PlayerName);
            ChoiceInput(1);
            area = 100; // ending area
            
        }
        else if(area == 100){
            // thank you message and final input
            printf("THANKS FOR PLAYING TIL THE END.\nYou are probably from my C class, so tell me what you thought.\nIt was kind of rushed towards the end, but I had a lot of fun making it.\nHope you had fun playing.\nHope I get full marks.\n\nThanks again\n-Uami\n\n1. End\n");
            ChoiceInput(1);
            GameOn = 0;
        }
        Sleeps(2000);
        ClearScreen();
        
    }
    free(PlayerName);
}