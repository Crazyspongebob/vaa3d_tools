function obj = joinAxons(obj)
if (obj.state.display.ch1==1) && isfield(obj.data.ch(1),'binaryArray')
    ch=1;
end
if (obj.state.display.ch2==1) && isfield(obj.data.ch(2),'binaryArray')
    ch=2;
end
numstr=char(obj.state.display.editbox);
if (numstr)
    dendrites=[];
    remain=numstr;
   while(remain)
    [token,remain]=strtok(remain,[' ',',',';']);
    [den,ok]=str2num(token);
    if (ok) & (den>0)
        dendrites=[dendrites den];
    else
        if token(1)~='-'
            
            den=double(token(1))-64;
        else
            den=64-double(token(2));
        end
        dendrites=[dendrites den];
    end
end
    newdendrites=[];
    if isfield(obj.data,'dendrites') && size(obj.data.dendrites,2)>1
        % find the closest endings
        first=[obj.data.dendrites(dendrites(1)).start' obj.data.dendrites(dendrites(1)).start' obj.data.dendrites(dendrites(1)).end' obj.data.dendrites(dendrites(1)).end'];
        second=[obj.data.dendrites(dendrites(2)).start' obj.data.dendrites(dendrites(2)).end' obj.data.dendrites(dendrites(2)).start' obj.data.dendrites(dendrites(2)).end'];
        [dis,ind]=min(sum(((first-second).*(first-second))));    
        switch ind
            case 1
                voxel1=fliplr(obj.data.dendrites(dendrites(1)).voxel);
                voxel2=obj.data.dendrites(dendrites(2)).voxel;
            case 2
                voxel1=fliplr(obj.data.dendrites(dendrites(1)).voxel);
                voxel2=fliplr(obj.data.dendrites(dendrites(2)).voxel);
            case 3
                voxel1=obj.data.dendrites(dendrites(1)).voxel;
                voxel2=obj.data.dendrites(dendrites(2)).voxel;
            case 4
                voxel1=obj.data.dendrites(dendrites(1)).voxel;
                voxel2=fliplr(obj.data.dendrites(dendrites(2)).voxel);
        end
        voxel1=double(voxel1);
        voxel2=double(voxel2)+0.00001;
        % figure out the linear link between the two axons
        dis=-double(voxel1(:,end))+double(voxel2(:,1));
        voxel=[voxel1(1,end):dis(1)/max(abs(dis)):voxel2(1,1); voxel1(2,end):dis(2)/max(abs(dis)):voxel2(2,1); voxel1(3,end):dis(3)/max(abs(dis)):voxel2(3,1); voxel1(4,end):dis(4)/max(abs(dis)):voxel2(4,1)];
        voxel=round(voxel);
         %smoothing around the area of linkage

        voxel(1,:)=smooth(voxel(1,:),7)';
        voxel(2,:)=smooth(voxel(2,:),7)';
        voxel(3,:)=smooth(voxel(3,:),7)';
        voxel=[voxel1'; voxel(:,2:end-1)'; voxel2']';
       
    
       
       [voxel, voxelmax, maxint, dx, dy] =shiftDendriteMax(double(voxel),obj.data.ch(ch).filteredArray,1);
        voxel=round(voxel);
        obj.data.dendrites(dendrites(1)).start=voxel(1:3,1)';
        obj.data.dendrites(dendrites(1)).end=voxel(1:3,end)';
   
       [maxint,voxelmax]=getbackboneintensity(double(voxel),obj.data.ch(ch).filteredArray,dx,dy,3,1,0);       
       obj.data.dendrites(dendrites(1)).voxel=uint16(floor(voxel));
       obj.data.dendrites(dendrites(1)).voxelmax=voxelmax;
       maxint=double(maxint);
       maxint=maxint-double(obj.data.ch(ch).imagemedian);
       obj.data.dendrites(dendrites(1)).maxintraw=maxint;
       obj.data.dendrites(dendrites(1)).maxint=reflectivesmooth(maxint,7);
       obj.data.dendrites(dendrites(1)).dx=dx;
       obj.data.dendrites(dendrites(1)).dy=dy;
       obj.data.dendrites(dendrites(1)).start=double(obj.data.dendrites(dendrites(1)).voxel(1:3,1))';
       obj.data.dendrites(dendrites(1)).end=double(obj.data.dendrites(dendrites(1)).voxel(1:3,end))';
       obj.data.dendrites(dendrites(1)).sizeofaxon=size(voxel,2);
       
       % median filtering
       % cut off tall peaks before filtering
       medianmaxint=median(maxint);
       left=maxint(maxint<medianmaxint);
       cutthres=std([left-medianmaxint medianmaxint-left]);
       maxintcut=maxint;
       maxintcut(maxint>medianmaxint+cutthres*1)=deal(medianmaxint+cutthres*1); 
       ns=obj.parameters.threedma.backbonemedian;
       if (size(maxintcut,2)>ns)
           medianfiltered=medfilt1([fliplr(maxintcut(1:ns)) maxintcut fliplr(maxintcut(end-ns+1:end))],ns);
           medianfiltered=medianfiltered(ns+1:end-ns);
       else
           medianfiltered=medfilt1([ones(1,ns)*maxintcut(1) maxintcut ones(1,ns)*maxintcut(end)],ns);
           medianfiltered=medianfiltered(ns+1:end-ns);
       end
       obj.data.dendrites(dendrites(1)).meanback=median(maxint);
       obj.data.dendrites(dendrites(1)).medianfiltered=medianfiltered;     
        
        %smoothing around the area of linkage
       obj.data.dendrites(dendrites(2))=[];
    end
    
    obj=ShiftDendriteMaxObj(obj,0); 
    obj=CorrectDendrites(obj);
    obj.data.spines=[];
end