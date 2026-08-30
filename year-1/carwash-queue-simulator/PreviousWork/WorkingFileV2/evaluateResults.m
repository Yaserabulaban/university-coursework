function evaluateResults(car_Interval, car_Counters)
    % Calculate and display evaluation results
    total_waiting_time = 0;
    total_service_time = 0;
    total_interarrival_time = 0;
    total_cars = sum(cellfun(@(x) size(x, 1), car_Counters));
    
    for i = 1:length(car_Counters)
        if ~isempty(car_Counters{i})
            total_service_time = total_service_time + sum(car_Counters{i}(:, 2));
            total_waiting_time = total_waiting_time + sum(car_Counters{i}(:, 3));
        end
    end
    
    total_interarrival_time = sum(car_Interval);
    
    avg_waiting_time = total_waiting_time / total_cars;
    avg_service_time = total_service_time / total_cars;
    avg_interarrival_time = total_interarrival_time / (total_cars - 1);
    avg_arrival_time = total_interarrival_time / total_cars;
    avg_time_spent = avg_waiting_time + avg_service_time;
    
    fprintf('\nEvaluation Results:\n');
    fprintf('Average waiting time: %.2f minutes\n', avg_waiting_time);
    fprintf('Average service time: %.2f minutes\n', avg_service_time);
    fprintf('Average inter-arrival time: %.2f minutes\n', avg_interarrival_time);
    fprintf('Average arrival time: %.2f minutes\n', avg_arrival_time);
    fprintf('Average time spent in system: %.2f minutes\n', avg_time_spent);
    fprintf('Probability of waiting: %.2f%%\n', (total_waiting_time / (total_cars * avg_service_time)) * 100);
end
