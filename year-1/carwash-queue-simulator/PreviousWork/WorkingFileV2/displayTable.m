function displayTable(carArray)
    fprintf('Car No. | Service Time | Interarrival Time\n');
    fprintf('-----------------------------------------------\n');
    for i = 1:size(carArray, 1)
        fprintf('%6d | %12d | %17d\n', carArray(i, 1), carArray(i, 2), carArray(i, 3));
    end
    fprintf('-----------------------------------------------\n');
end
