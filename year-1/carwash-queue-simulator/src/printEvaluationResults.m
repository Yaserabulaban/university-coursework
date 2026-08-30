function printEvaluationResults(results, serviceTypes_Data)
    fprintf('======================== E V A L U A T I O N =======================\n');
    fprintf('Average Waiting Time: %d hours %d minutes\n', floor(results.avg_waiting_time / 60), mod(results.avg_waiting_time, 60));
    fprintf('Average Service Time: %d hours %d minutes\n', floor(results.avg_service_time / 60), mod(results.avg_service_time, 60));
    fprintf('Average Time in System: %d hours %d minutes\n', floor(results.avg_time_in_system / 60), mod(results.avg_time_in_system, 60));
    fprintf('Average Arrival Time: %d hours %d minutes\n', floor(results.avg_arrival_time / 60), mod(results.avg_arrival_time, 60));
    fprintf('Average Inter-Arrival Time: %d hours %d minutes\n', floor(results.avg_interarrival_time / 60), mod(results.avg_interarrival_time, 60));
    fprintf('Probability of Waiting: %.2f\n', results.prob_waiting);
    fprintf('Total Cars Served: %d\n', results.total_cars_served);
    
    % Print the total number of cars taking each service type
    fprintf('Total Number of Cars for each Service Type:\n');
    for i = 1:length(results.service_type_counts)
        fprintf('%s: %d\n', serviceTypes_Data{1, i}, results.service_type_counts(i));
    end
end
