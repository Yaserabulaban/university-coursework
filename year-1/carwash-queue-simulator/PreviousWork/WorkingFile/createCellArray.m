function cellArray = createCellArray(serviceTimes, probabilities, cdf, ranges)
    cellArray = cell(4, length(serviceTimes));
    for i = 1:length(serviceTimes)
        cellArray{1, i} = serviceTimes(i);
        cellArray{2, i} = probabilities(i);
        cellArray{3, i} = cdf(i);
        cellArray{4, i} = ranges{i};
    end
end
