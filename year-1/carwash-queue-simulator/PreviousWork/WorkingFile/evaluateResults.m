function results = evaluateResults(statistics, car_Interval)
    total_cars = 0;
    total_waiting_time = 0;
    total_service_time = 0;
    total_time_in_system = 0;
    total_arrival_time = sum(car_Interval);
    total_interarrival_time = sum(diff(car_Interval));
    total_cars_waiting = 0;

    for i = 1:length(statistics)
        bay_data = statistics{i};
        total_cars = total_cars + size(bay_data, 1);
        for j = 1:size(bay_data, 1)
            total_waiting_time = total_waiting_time + bay_data{j, 7};
            total_service_time = total_service_time + bay_data{j, 4};
            total_time_in_system = total_time_in_system + bay_data{j, 8};
            if bay_data{j, 7} > 0
                total_cars_waiting = total_cars_waiting + 1;
            end
        end
    end

    results.total_cars = total_cars;
    results.avg_waiting_time = total_waiting_time / total_cars;
    results.avg_service_time = total_service_time / total_cars;
    results.avg_time_in_system = total_time_in_system / total_cars;
    results.avg_arrival_time = total_arrival_time / total_cars;
    results.avg_interarrival_time = total_interarrival_time / (total_cars - 1);
    results.prob_waiting = total_cars_waiting / total_cars;
end
