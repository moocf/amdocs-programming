#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;

// Structure for Position
typedef struct _Position
{
	int		x;
	int		y;
}Position;

// Structure for a Ship
typedef struct _Ship
{
	int		x;
	int		y;
	int		size;
}Ship;

// Structure of a Board
typedef struct _Board
{
	int		num;
	Ship	ship[6];
}Board;





// Global Variables
FILE		*fin, *fout;
Position	*attack;
int			num_attacks;

// Function Prototypes
void	initBoard(Board &arena);
int		shipHit(Board &arena, Position attck);
void	shipShift(Board &arena, int ship_no, int dir, int dist);
int		solve(Board arena, int att_no);



// Initialize the Board
void	initBoard(Board &arena)
{
	arena.num = 6;
	arena.ship[0].size = 4;
	arena.ship[0].x = 0;
	arena.ship[0].y = 0;
	arena.ship[1].size = 6;
	arena.ship[1].x = 2;
	arena.ship[1].y = 5;
    arena.ship[2].size = -5;
	arena.ship[2].x = 3;
	arena.ship[2].y = 6;
    arena.ship[3].size = -5;
	arena.ship[3].x = 9;
	arena.ship[3].y = 7;
    arena.ship[4].size = -3;
	arena.ship[4].x = 10;
	arena.ship[4].y = 1;
    arena.ship[5].size = -2;
	arena.ship[5].x = 8;
	arena.ship[5].y = 2;
}

// This function tells which Ship was hit by an attack
int		shipHit(Board &arena, Position attck)
{
	int		i;
	
	for(i=0; i<arena.num; i++)
	{
		if(attck.x < arena.ship[i].x) continue;
		if(attck.y < arena.ship[i].y) continue;
		if((attck.x != arena.ship[i].x) || (attck.y != arena.ship[i].y)) continue;
		if((arena.ship[i].size > 0) && (attck.x >= arena.ship[i].x) && (attck.x < (arena.ship[i].x + arena.ship[i].size))) return(i);
		if((arena.ship[i].size < 0) && (attck.y >= arena.ship[i].y) && (attck.y < (arena.ship[i].y - arena.ship[i].size))) return(i);
	}
	return(-1);
}

// This function shifts a ship
void	shipShift(Board &arena, int ship_no, int dir, int dist)
{
	if(dir == 1)
		arena.ship[ship_no].x = arena.ship[ship_no].x + dist;
	else
		arena.ship[ship_no].y = arena.ship[ship_no].y + dist;
}

// This function tells if a ship shift is possible
int		shipShiftPossible(Board &arena, int ship_no, int dir, int dist)
{
	int		i;
	return(1);
}

int		trySolveDir(Board arena, int ship_no, int att_no, int dir, int dist_step)
{
	int		k, n, max = 0, dist = dist_step;
	
	while((k = shipShiftPossible(arena, ship_no, dir, dist)) != -1)
	{
		// If Ship shift possible
		if(k == 1)
		{
			shipShift(arena, ship_no, dir, dist);
			n = solve(arena, att_no + 1);
			if(n > max) max = n;
		}
		dist += dist_step;
	}
	return(max);
}

// Recursive function to solve the Arena
int		solve(Board arena, int att_no)
{
	Board	arena2;
	int		max, k, hit_ship;
	
	// Terminating Condition
	if(att_no >= num_attacks) return(att_no);
	
	// Check if a ship was hit
	hit_ship = shipHit(arena, attack[att_no]);
	// No ship was hit
	if(hit_ship < 0)
	{
		return(solve(arena, att_no + 1));
	}
	// Some ship was hit
	else
	{
		// Find all alternative positions for the ship
		max = 0;
		k = trySolveDir(arena, hit_ship, att_no, 1, -1);
		if(k > max) k = max;
		k = trySolveDir(arena, hit_ship, att_no, 1, 1);
		if(k > max) k = max;
		k = trySolveDir(arena, hit_ship, att_no, -1, -1);
		if(k > max) k = max;
		k = trySolveDir(arena, hit_ship, att_no, -1, 1);
		if(k > max) k = max;
	}
	return(max);
}

// Main Logic
void	run()
{
	int		i, N, x, y;
	char	*x_s;
	
	// Initialize the Board
	Board	arena;
	initBoard(arena);

	// Main loop for getting the test cases
	while(1)
	{
		// Get the number of attacks
		fscanf(fin, "%d", &N);
		if(N == 0) break;
		attack = new Position[N];
		// Get the attacks
		for(i=0; i<N; i++)
		{
			fscanf(fin, "%d%c", &y, &x_s);
			x = (int)(x_s - 'A');
			attack[i].x = x;
			attack[i].y = y;
		}
		// Get the result
		fprintf(fout, "%d\n", solve(arena, 0) );
		// Clean up
		delete attack;
	}
	fscanf(fin, "%d", &N);
}



// Main Function
int main(int argc, char *argv[])
{
	// Open the Input and Output Files
	if(argc != 3) return(0);
	fin = fopen(argv[1], "r+");
	fout = fopen(argv[2], "w+");
	
	// Main Code
	run();
	
	// Close the Input and Output Files
	fclose(fin);
	fclose(fout);
    return(0);
}


