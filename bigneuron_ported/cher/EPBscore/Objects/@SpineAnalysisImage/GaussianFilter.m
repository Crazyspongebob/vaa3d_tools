function obj = GaussianFilter(obj)
if isfield(obj.data,'imageArray')
%     if (obj.state.GUI==1)
%         w = waitbar(0.1,'Filtering of Tif', 'Name', 'GaussianFiltering XY');
%     end
%     close(w);
%     neigh=obj.parameters.threedma.medianneighborhood;
%     obj.data.gaussianArray=uint16(smooth3(obj.data.imageArray,'box',[neigh neigh 1]));
%     %obj.data.filteredArray=obj.data.gaussianArray;
    if (obj.state.GUI==1)
        w = waitbar(0.1,'Filtering of Tif', 'Name', 'WienerFiltering XY');
    end
    total=size(obj.data.imageArray,3);
    counter=0;
    obj.data.medianArray=[];
    image=double(obj.data.imageArray(:));
    obj.data.imagemedian=median(image);
    obj.data.imagestd=std([image(image<obj.data.imagemedian);2*obj.data.imagemedian-image(image<obj.data.imagemedian)]);       
    imedian=obj.data.imagemedian;
     neigh=obj.parameters.threedma.medianneighborhood;
     obj.data.gaussianArray=uint16(smooth3(obj.data.imageArray,'gaussian',[neigh neigh 1]));
%     for i = 1:total
%         if (obj.state.GUI==1)
%             waitbar(counter/total,w,['Filtering frame ' num2str(counter) ' of ' num2str(total)]);
%         end
%         counter=counter+1;
%         neigh=obj.parameters.threedma.medianneighborhood;
%         obj.data.gaussianArray(:,:,i)=double(wiener2(obj.data.imageArray(:,:,i),[neigh neigh]));
%     end
    close(w);
    obj.state.refiltered=1;
end    