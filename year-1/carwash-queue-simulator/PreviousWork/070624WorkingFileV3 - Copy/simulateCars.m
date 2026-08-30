function simulateCars(Number_Of_Cars, car_Interval, car_WashBays)
    % Simulate car arrivals and services
    for i = 1:Number_Of_Cars
        fprintf('Arrival of car %d at minute %d\n', i, car_Interval(i));
        
        % Debug: Check car_WashBays content for each wash bay
        disp('Debug: Checking car_WashBays content');
        for j = 1:3
            disp(['Wash bay ', num2str(j), ':']);
            disp(car_WashBays{j});
        end

        for j = 1:3
            if i <= size(car_WashBays{j}, 1)
                fprintf('Service for car %d started at minute %d in wash bay %d\n', car_WashBays{j}(i, 1), car_Interval(i), j);
                fprintf('Service for car %d ended at minute %d in wash bay %d\n', car_WashBays{j}(i, 1), car_Interval(i) + car_WashBays{j}(i, 2), j);
            end
        end
    end
end
