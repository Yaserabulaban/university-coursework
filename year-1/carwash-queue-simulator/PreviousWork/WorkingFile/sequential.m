function sequential(cars)
    % Simulate car wash with sequential bay assignment
    numCars = cars.NumCars;
    serviceTime = cars.ServiceTime;
    interArrivalTime = cars.InterArrivalTime;
    
    arrivalTime = cumsum(interArrivalTime);
    washEndTime = zeros(1, numCars);
    
    for i = 1:numCars
        bay = mod(i-1, 3) + 1; % Assign sequentially to bays 1, 2, 3
        startTime = arrivalTime(i);
        endTime = startTime + serviceTime(i);
        washEndTime(i) = endTime;
        
        % Print arrival and departure messages
        fprintf('Arrival of car %d at minute %.2f and queue at the bay %d\n', i, arrivalTime(i), bay);
        fprintf('Service for car %d started at minute %.2f and ended at minute %.2f\n', i, startTime, endTime);
    end
    
    % Print overall statistics
    fprintf('\nOverall Statistics:\n');
    fprintf('Average waiting time: %.2f minutes\n', mean(washEndTime - arrivalTime));
end
