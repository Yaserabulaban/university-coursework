function IdleBay(cars)
    % Simulate car wash with idle bay selection
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
        
        % Print arrival and departure messages
        fprintf('Arrival of car %d at minute %.2f and queue at the bay %d\n', i, arrivalTime(i), bay);
        fprintf('Service for car %d started at minute %.2f and ended at minute %.2f\n', i, startTime, endTime);
    end
    
    % Print overall statistics
    fprintf('\nOverall Statistics:\n');
    fprintf('Average waiting time: %.2f minutes\n', mean(washEndTime - arrivalTime));
end
