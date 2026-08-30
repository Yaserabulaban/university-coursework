function printBays(cars)
    % Print the state of each wash bay at the end of the simulation
    numCars = cars.NumCars;
    serviceTime = cars.ServiceTime;
    interArrivalTime = cars.InterArrivalTime;
    
    arrivalTime = cumsum(interArrivalTime);
    washEndTime = zeros(1, numCars);
    bayBusy = zeros(1, 3); % 3 wash bays
    
    for i = 1:numCars
        % Find the first idle bay or select bay 1 if all are busy
        bay = find(bayBusy <= arrivalTime(i), 1);
        if isempty(bay)
            bay = 1;
        end
        
        % Start service
        startTime = max(arrivalTime(i), bayBusy(bay));
        endTime = startTime + serviceTime(i);
        
        % Update bay status and wash end time
        bayBusy(bay) = endTime;
        washEndTime(i) = endTime;
    end
    
    % Print the detailed simulation table for each bay
    fprintf('\nDetailed Simulation Table:\n');
    fprintf('Car\tArrival Time\tService Time\tStart Time\tEnd Time\n');
    for i = 1:numCars
        fprintf('%d\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n', i, arrivalTime(i), serviceTime(i), max(arrivalTime(i), bayBusy(mod(i-1, 3) + 1)), washEndTime(i));
    end
end
