function results = evaluateResults(statistics, car_Interval, serviceTypes_Data)
    % Initialize variables for total cars and service type counts
    totalCarsServed = 0;
    serviceTypeCounts = zeros(1, length(serviceTypes_Data(1, :)));

    % Calculate totals and counts
    totalWaitingTime = 0;
    totalServiceTime = 0;
    totalTimeInSystem = 0;
    totalInterarrivalTime = 0;
    carsThatWaited = 0;

    for i = 1:length(statistics)
        totalCarsServed = totalCarsServed + size(statistics{i}, 1);
        for j = 1:size(statistics{i}, 1)
            totalWaitingTime = totalWaitingTime + statistics{i}{j, 7}; % 7th column is waiting time
            totalServiceTime = totalServiceTime + statistics{i}{j, 4}; % 4th column is service time
            totalTimeInSystem = totalTimeInSystem + statistics{i}{j, 8}; % 8th column is time in system
            if statistics{i}{j, 7} > 0
                carsThatWaited = carsThatWaited + 1;
            end
            serviceType = statistics{i}{j, 9}; % 9th column is service type
            serviceTypeIndex = find(strcmp(serviceType, serviceTypes_Data(1, :)), 1);
            if ~isempty(serviceTypeIndex)
                serviceTypeCounts(serviceTypeIndex) = serviceTypeCounts(serviceTypeIndex) + 1;
            end
        end
    end

    for i = 2:length(car_Interval)
        totalInterarrivalTime = totalInterarrivalTime + car_Interval(i); % Corrected interarrival time calculation
    end

    % Store results
    results.avg_waiting_time = totalWaitingTime / totalCarsServed;
    results.avg_service_time = totalServiceTime / totalCarsServed;
    results.avg_time_in_system = totalTimeInSystem / totalCarsServed;
    results.avg_arrival_time = sum(car_Interval) / totalCarsServed;
    results.avg_interarrival_time = totalInterarrivalTime / (length(car_Interval) - 1);
    results.prob_waiting = carsThatWaited / totalCarsServed;
    results.total_cars_served = totalCarsServed;
    results.service_type_counts = serviceTypeCounts;
end
