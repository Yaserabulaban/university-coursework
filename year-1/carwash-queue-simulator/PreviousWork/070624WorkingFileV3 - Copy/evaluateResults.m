function evaluateResults(car_Interval, car_Counters)
    total_waiting_time = 0;
    total_service_time = 0;
    total_time_in_system = 0;
    num_cars = sum(cellfun(@(x) size(x, 1), car_Counters));

    % Debug: Check initial values
    disp('Debug: Initial values');
    disp('car_Interval:');
    disp(car_Interval);
    disp('car_Counters:');
    disp(car_Counters);
    
    for i = 1:3
        for j = 1:size(car_Counters{i}, 1)
            waiting_time = car_Interval(j);
            service_time = car_Counters{i}(j, 2);
            time_in_system = waiting_time + service_time;
            
            total_waiting_time = total_waiting_time + waiting_time;
            total_service_time = total_service_time + service_time;
            total_time_in_system = total_time_in_system + time_in_system;
        end
    end

    % Debug: Check aggregated values
    disp('Debug: Aggregated values');
    disp('total_waiting_time:');
    disp(total_waiting_time);
    disp('total_service_time:');
    disp(total_service_time);
    disp('total_time_in_system:');
    disp(total_time_in_system);

    avg_waiting_time = total_waiting_time / num_cars;
    avg_service_time = total_service_time / num_cars;
    avg_time_in_system = total_time_in_system / num_cars;
    
    fprintf('Average Waiting Time: %.2f minutes\n', avg_waiting_time);
    fprintf('Average Service Time: %.2f minutes\n', avg_service_time);
    fprintf('Average Time in System: %.2f minutes\n', avg_time_in_system);
end
