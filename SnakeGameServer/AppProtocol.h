#pragma once
#include <string>

typedef enum USERLOCATION {
	MENU_DOMAIN = 0,
	SCORE_DOMAIN = 1,
	GAME_DOMAIN = 2,
	IN_GAME_DOMAIN = 3
} USERLOCATION;

typedef enum USERCONNECTION {
	UNHEALTHY = 0,
	HEALTHY = 1
} USERCONNECTION;

typedef enum INGAMESTATUS {
	DEAD = 0,
	ALIVE = 1
} INGAMESTATUS;

typedef enum GAMEMODE {
	NORMAL = 0,
	LARGE = 1
} GAMEMODE;

typedef enum RECV_OPCODE {
	S_RECV_ERROR = 1,			
	S_RECV_PONG = 2,
	S_RECV_EXIT = 3,

	S_RECV_USER_NAME_INFO = 100, // ASK USER NAME AFTER CONNECTION ESTABLISHED
	S_RECV_MAIN_MENU_SELECT = 101, // MAIN MENU 1. GAME PLAY, 2. SHOW SCORE, 3. EXIT
	S_RECV_GAME_MODE_SELECT = 102, // GAME MODE 1. 15X15, 2. 20X20
	S_RECV_SCORE_MODE_SELECT = 103, // SCORE MODE 1. 15X15, 2. 20X20

	S_RECV_TURN_RIGHT = 200,
	S_RECV_TURN_LEFT = 201,
	S_RECV_TURN_UP = 202,
	S_RECV_TURN_DOWN = 203,
	S_RECV_NEW_TAIL_REQUEST = 204
} RECV_OPCODE;

typedef enum SEND_OPCODE {
	S_SEND_ERROR = 51,
	S_SEND_PING = 52,
	S_SEND_ACCEPT_CONNECTION = 53, // POPULATE MAIN MENU
	S_SEND_TERMINATE_CONNECTION = 54,

	S_SEND_SHOW_GAME_MODE = 500,
	S_SEND_SHOW_SCORE_MODE = 501,
	S_SEND_SHOW_SCORE = 502,
	S_SEND_BACK_TO_MAIN = 503,

	S_SEND_GAME_START = 600, // WAIT 3 SEC THEN GAME START
	S_SEND_MOVE_INFO = 601, // SEND NEW COORDINATE OF SNAKE HEAD
	S_SEND_CHANGE_DIRECTION = 602,
	S_SEND_NEW_TAIL_POPULATE = 603, // NEW TAIL POPULATE ON THE MAP - MAXIMUM 3
	S_SEND_NEW_TAIL_APPEND = 604, // NEW SNAKE TAIL IS ON THE NEW COORDINATE, APPEND IT
	S_SEND_SNAKE_DEAD = 605 // NEW COORDINATE INDICATED COLLISION
} SEND_OPCODE;

typedef struct PACKET
{
	int opcode;			// opcode
	std::string data;	// packet data
} PACKET;

