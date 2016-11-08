/*Baisc implemtation of conways game of life
  This uses a fixed size world
  Inital posistion of life is hard coded
  print only to console window
  */

#include <iostream>
#include <vector>
#include <random>

  //random number generator
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_int_distribution<int> distribution(0, 1);

std::vector<std::vector<int>> world;
std::vector<std::vector<int>> world_temp;

int size_x, size_y, generations;

int main()
{
	int current_gen = 1;

	std::cout << "Enter size of the world (x,y): ";
	std::cin >> size_x;
	while (size_x <= 0) {
		std::cout << "Size of X not valid. The world must be greater than 0";
		std::cin >> size_x;
	}
	std::cin >> size_y;
	while (size_y <= 0) {
		std::cout << "Size of Y not valid. The world must be greater than 0";
		std::cin >> size_y;
	}

	for (int i = 0; i < size_y; i++) {
		std::vector<int> row;
		for (int j = 0; j < size_x; j++) {
			row.push_back(distribution(generator));
		}
		world.push_back(row);
	}

	//generate temp world to store next generation in
	for (int i = 0; i < size_y; i++) {
		std::vector<int> rowb;
		for (int j = 0; j < size_x; j++) {
			rowb.push_back(0);
		}
		world_temp.push_back(rowb);
	}

	//std::cout << std::endl << std::endl << "temp world view init" << std::endl;
	//for (int i = 0; i < size_y; i++) {
	//	for (int j = 0; j < size_x; j++) {
	//		std::cout << world_temp[i][j] << "  ";
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;

	std::cout << std::endl << std::endl << "Inital world view" << std::endl;
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			std::cout << world[i][j] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Enter the maxmiun number of generations: ";
	std::cin >> generations;
	while (generations <= 0) {
		std::cout << "The number of generations must be greater than 0";
		std::cin >> generations;
	}

	std::cout << std::endl << "Simulation has begun" << std::endl << "--------------------" << std::endl << std::endl;

	//Run simulation

	int Previous_population_total = 0;
	int Population_2gena_ago = 0;

	while (current_gen <= generations) {
		int Total_Population = 0;

		for (int i = 0; i < size_y; i++) {
			for (int j = 0; j < size_x; j++) {
				int number_of_cells = 0;

				//Conditional limits
				int lower_limit_Y = i - 1;
				int lower_limit_X = j - 1;
				int upper_limit_Y = i + 1;
				int upper_limit_X = j + 1;

				if (lower_limit_Y < 0) { lower_limit_Y = 0; }
				if (lower_limit_X < 0) { lower_limit_X = 0; }
				if (upper_limit_Y >= size_y) { upper_limit_Y = size_y - 1; }
				if (upper_limit_X >= size_x) { upper_limit_X = size_x - 1; }
				int testcount = 0;

				//Calulate the number of live cells around the current one using limits.
				for (int Y = lower_limit_Y; Y <= upper_limit_Y; Y++) {
					for (int X = lower_limit_X; X <= upper_limit_X; X++) {
						if (world[Y][X] == 1) { number_of_cells++; }
						testcount++;
					}
				}

				if (world[i][j] == 1) {
					number_of_cells--;
					if (number_of_cells < 2) { world_temp[i][j] = 0; }
					else if (number_of_cells == 2 || number_of_cells == 3) { world_temp[i][j] = 1; }
					else if (number_of_cells > 3) { world_temp[i][j] = 0; }
				}

				if (number_of_cells == 3) { world_temp[i][j] = 1; }
			}
		}

		//update game world
		for (int i = 0; i < size_y; i++) {
			for (int j = 0; j < size_x; j++) {
				world[i][j] = world_temp[i][j];
				world_temp[i][j] = 0;
			}
		}

		std::cout << std::endl << "Generation = " << current_gen << std::endl;
		for (int i = 0; i < size_y; i++) {
			for (int j = 0; j < size_x; j++) {
				std::cout << world[i][j] << "  ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		//check to see if life is still present
		for (int i = 0; i < size_y; i++) {
			for (int j = 0; j < size_x; j++) {
				if (world[i][j] == 1) { Total_Population++; }
			}
		}

		std::cout << "Total population = " << Total_Population << std::endl;
		std::cout << "The previous population = " << Previous_population_total << std::endl;

		if (Total_Population == 0) {
			std::cout << "The apocalypse has happend, all life has been wiped out within " << current_gen << " generations." << std::endl << std::endl << "Simuation Terminated!" << std::endl << "---------------------";
			break;
		}

		else if (Total_Population > Previous_population_total) {
			std::cout << "Population is increasing." << std::endl;
		}

		else if (Total_Population < Previous_population_total) {
			std::cout << "Population is decreasing." << std::endl;
		}

		else if (Total_Population == Previous_population_total && Previous_population_total == Population_2gena_ago) {
			std::cout << "The population is stagnet." << std::endl;
		}

		else if (current_gen == generations) {
			std::cout << "Simulation has finished." << std::endl;
			std::cout << "------------------------" << std::endl;
		}

		Previous_population_total = Total_Population;
		Population_2gena_ago = Previous_population_total;

		current_gen++;
	}

	return 0;
};