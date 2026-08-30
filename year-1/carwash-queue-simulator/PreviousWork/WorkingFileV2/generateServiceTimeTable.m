function data = generateServiceTimeTable(washBay, rng_type)
    fprintf('\n%s:\n', washBay);
    num_rows = 5; % Assuming 5 rows for simplicity
    data = zeros(num_rows, 2);
    for i = 1:num_rows
        data(i, 1) = randi([5, 15]); % Generate integer between 5 and 15
        data(i, 2) = rand() / num_rows; % Example probability
    end
    displayServiceTime(data);
end
