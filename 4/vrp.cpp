#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include "google/protobuf/duration.pb.h"
#include "ortools/constraint_solver/routing.h"
#include "ortools/constraint_solver/routing_enums.pb.h"
#include "ortools/constraint_solver/routing_index_manager.h"
#include "ortools/constraint_solver/routing_parameters.h"

struct Point 
{
	double x;
	double y;
};

double dist(Point p1, Point p2) 
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

namespace operations_research 
{
	struct DataModel 
	{
		std::vector<std::vector<double>> distance_matrix;
		std::vector<int64_t> demands;
		std::vector<int64_t> vehicle_capacities;
		int64_t num_vehicles = 0;
		RoutingIndexManager::NodeIndex depot{0};
	};

	void PrintSolution(const DataModel& data, const RoutingIndexManager& manager,
			const RoutingModel& routing, const Assignment& solution) 
	{
		int64_t total_distance{0};
		int64_t total_load{0};
		for (int vehicle_id = 0; vehicle_id < data.num_vehicles; ++vehicle_id) 
		{
			int64_t index = routing.Start(vehicle_id);
			int64_t route_distance{0};
			int64_t route_load{0};
			std::stringstream route;
			while (routing.IsEnd(index) == false) 
			{
				int64_t node_index = manager.IndexToNode(index).value();
				route_load += data.demands[node_index];
				int64_t previous_index = index;
				index = solution.Value(routing.NextVar(index));
				route_distance += routing.GetArcCostForVehicle(previous_index, index,
						int64_t{vehicle_id});
			}
			total_distance += route_distance;
			total_load += route_load;
		}
		std::cout << total_distance << std::endl;
	}
	void VrpCapacity(DataModel init_data) 
	{
		DataModel data = init_data;
		RoutingIndexManager manager(data.distance_matrix.size(), data.num_vehicles,
				data.depot);
		RoutingModel routing(manager);
		const int transit_callback_index = routing.RegisterTransitCallback(
				[&data, &manager](int64_t from_index, int64_t to_index) -> int64_t 
				{
				int from_node = manager.IndexToNode(from_index).value();
				int to_node = manager.IndexToNode(to_index).value();
				return data.distance_matrix[from_node][to_node];
				});
		routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index);
		const int demand_callback_index = routing.RegisterUnaryTransitCallback(
				[&data, &manager](int64_t from_index) -> int64_t 
				{
				int from_node = manager.IndexToNode(from_index).value();
				return data.demands[from_node];
				});
		routing.AddDimensionWithVehicleCapacity(
				demand_callback_index,
				int64_t{0},
				data.vehicle_capacities,
				true,
				"Capacity");
		RoutingSearchParameters search_parameters = DefaultRoutingSearchParameters();
		search_parameters.set_first_solution_strategy(
				FirstSolutionStrategy::PATH_CHEAPEST_ARC);
		search_parameters.set_local_search_metaheuristic(
				LocalSearchMetaheuristic::GUIDED_LOCAL_SEARCH);
		search_parameters.mutable_time_limit()->set_seconds(300);
		const Assignment* solution = routing.SolveWithParameters(search_parameters);
		PrintSolution(data, manager, routing, *solution);
	}
}

int main(int argc, char** argv) 
{
	int64_t N = 0, num_vehicles_one = 0, vehicle_capacities_one = 0, z1 = 0;
	char *filename = 0;
	if (argc != 2)
	{
		printf("Usage: %s input\n", argv[0]);
		return 1;
	}
	filename = argv[1];
	FILE *f;
	f = fopen(filename, "r");
	if (fscanf(f, "%ld", &z1) == 1)
	{
		N = z1;
	}
	if (fscanf(f, "%ld", &z1) == 1)
	{
		num_vehicles_one  = z1;
	}
	if (fscanf(f, "%ld", &z1) == 1)
	{
		vehicle_capacities_one = z1;
	}
	std::vector<int64_t> buffer(num_vehicles_one, vehicle_capacities_one);
	operations_research::DataModel data;
	data.vehicle_capacities = buffer;
	data.num_vehicles = num_vehicles_one;
	std::vector<Point> points(N);
	std::vector<int64_t> buf(N);
	for (int i = 0; i < N; i++)
	{
		int64_t demand;
		Point p;
		if (fscanf(f, "%ld", &z1) == 1)
		{
			demand = z1;
		}
		if (fscanf(f, "%ld", &z1) == 1)
		{
			p.x = z1;
		}
		if (fscanf(f, "%ld", &z1) == 1)
		{
			p.y = z1;
		}
		points[i] = p;
		buf[i] = demand;
	}
	std::vector<std::vector<double> > mas(N, std::vector<double>(N));
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++) 
		{
			if (i == j) 
			{
				mas[i][j] = 0;
			}
			else 
			{
				mas[i][j] = dist(points[i], points[j]);
			}
		}
	}
	data.demands = buf;
	data.distance_matrix = mas;
	operations_research::VrpCapacity(data);
	fclose(f);
	return EXIT_SUCCESS;
}
