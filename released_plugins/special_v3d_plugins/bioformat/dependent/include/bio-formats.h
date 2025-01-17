//
// bio-formats.h
//

/*
OME Bio-Formats C++ bindings for native access to Bio-Formats Java library.
Copyright (C) 2008-2009 UW-Madison LOCI and Glencoe Software, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*-----------------------------------------------------------------------------
 *
 * THIS IS AUTOMATICALLY GENERATED CODE.  DO NOT MODIFY.
 * Created by curtis via JaceHeaderAutogen on Oct 28, 2009 2:24:12 PM CDT
 *
 *-----------------------------------------------------------------------------
 */

#ifndef BIO_FORMATS_H
#define BIO_FORMATS_H

#include "jace.h"

#include "jace/proxy/loci/formats/AxisGuesser.h"
#include "jace/proxy/loci/formats/ChannelFiller.h"
#include "jace/proxy/loci/formats/ChannelMerger.h"
#include "jace/proxy/loci/formats/ChannelSeparator.h"
#include "jace/proxy/loci/formats/ClassList.h"
#include "jace/proxy/loci/formats/CoreMetadata.h"
#include "jace/proxy/loci/formats/DelegateReader.h"
#include "jace/proxy/loci/formats/DimensionSwapper.h"
#include "jace/proxy/loci/formats/FileInfo.h"
#include "jace/proxy/loci/formats/FilePattern.h"
#include "jace/proxy/loci/formats/FileStitcher.h"
#include "jace/proxy/loci/formats/FormatException.h"
#include "jace/proxy/loci/formats/FormatHandler.h"
#include "jace/proxy/loci/formats/FormatReader.h"
#include "jace/proxy/loci/formats/FormatTools.h"
#include "jace/proxy/loci/formats/FormatWriter.h"
#include "jace/proxy/loci/formats/IFormatHandler.h"
#include "jace/proxy/loci/formats/IFormatReader.h"
#include "jace/proxy/loci/formats/IFormatWriter.h"
#include "jace/proxy/loci/formats/ImageReader.h"
#include "jace/proxy/loci/formats/ImageTools.h"
#include "jace/proxy/loci/formats/ImageWriter.h"
#include "jace/proxy/loci/formats/MetadataTools.h"
#include "jace/proxy/loci/formats/MinMaxCalculator.h"
#include "jace/proxy/loci/formats/MissingLibraryException.h"
#include "jace/proxy/loci/formats/NetcdfTools.h"
#include "jace/proxy/loci/formats/NumberFilter.h"
#include "jace/proxy/loci/formats/POITools.h"
#include "jace/proxy/loci/formats/ReaderWrapper.h"
#include "jace/proxy/loci/formats/StatusEvent.h"
#include "jace/proxy/loci/formats/StatusListener.h"
#include "jace/proxy/loci/formats/StatusReporter.h"
#include "jace/proxy/loci/formats/UnknownFormatException.h"
#include "jace/proxy/loci/formats/WriterWrapper.h"
//using namespace jace::proxy::loci::formats;

#include "jace/proxy/loci/formats/cache/ByteArraySource.h"
#include "jace/proxy/loci/formats/cache/Cache.h"
#include "jace/proxy/loci/formats/cache/CacheEvent.h"
#include "jace/proxy/loci/formats/cache/CacheException.h"
#include "jace/proxy/loci/formats/cache/CacheListener.h"
#include "jace/proxy/loci/formats/cache/CacheReporter.h"
#include "jace/proxy/loci/formats/cache/CacheSource.h"
#include "jace/proxy/loci/formats/cache/CacheStrategy.h"
#include "jace/proxy/loci/formats/cache/CacheUpdater.h"
#include "jace/proxy/loci/formats/cache/CrosshairStrategy.h"
#include "jace/proxy/loci/formats/cache/ICacheSource.h"
#include "jace/proxy/loci/formats/cache/ICacheStrategy.h"
#include "jace/proxy/loci/formats/cache/RectangleStrategy.h"
//using namespace jace::proxy::loci::formats::cache;

#include "jace/proxy/loci/formats/codec/Base64Codec.h"
#include "jace/proxy/loci/formats/codec/BaseCodec.h"
#include "jace/proxy/loci/formats/codec/BitBuffer.h"
#include "jace/proxy/loci/formats/codec/BitWriter.h"
#include "jace/proxy/loci/formats/codec/ByteVector.h"
#include "jace/proxy/loci/formats/codec/Codec.h"
#include "jace/proxy/loci/formats/codec/CodecOptions.h"
#include "jace/proxy/loci/formats/codec/HuffmanCodec.h"
#include "jace/proxy/loci/formats/codec/HuffmanCodecOptions.h"
#include "jace/proxy/loci/formats/codec/JPEG2000Codec.h"
#include "jace/proxy/loci/formats/codec/JPEG2000CodecOptions.h"
#include "jace/proxy/loci/formats/codec/JPEGCodec.h"
#include "jace/proxy/loci/formats/codec/LZOCodec.h"
#include "jace/proxy/loci/formats/codec/LZWCodec.h"
#include "jace/proxy/loci/formats/codec/LosslessJPEGCodec.h"
#include "jace/proxy/loci/formats/codec/LuraWaveCodec.h"
#include "jace/proxy/loci/formats/codec/MJPBCodec.h"
#include "jace/proxy/loci/formats/codec/MJPBCodecOptions.h"
#include "jace/proxy/loci/formats/codec/MSRLECodec.h"
#include "jace/proxy/loci/formats/codec/MSVideoCodec.h"
#include "jace/proxy/loci/formats/codec/NikonCodec.h"
#include "jace/proxy/loci/formats/codec/NikonCodecOptions.h"
#include "jace/proxy/loci/formats/codec/PackbitsCodec.h"
#include "jace/proxy/loci/formats/codec/QTRLECodec.h"
#include "jace/proxy/loci/formats/codec/RPZACodec.h"
#include "jace/proxy/loci/formats/codec/ZlibCodec.h"
//using namespace jace::proxy::loci::formats::codec;

#include "jace/proxy/loci/formats/enums/AcquisitionMode.h"
#include "jace/proxy/loci/formats/enums/ArcType.h"
#include "jace/proxy/loci/formats/enums/Binning.h"
#include "jace/proxy/loci/formats/enums/ContrastMethod.h"
#include "jace/proxy/loci/formats/enums/Correction.h"
#include "jace/proxy/loci/formats/enums/DetectorType.h"
#include "jace/proxy/loci/formats/enums/DimensionOrder.h"
#include "jace/proxy/loci/formats/enums/Enumeration.h"
#include "jace/proxy/loci/formats/enums/EnumerationException.h"
#include "jace/proxy/loci/formats/enums/EnumerationProvider.h"
#include "jace/proxy/loci/formats/enums/ExperimentType.h"
#include "jace/proxy/loci/formats/enums/FilamentType.h"
#include "jace/proxy/loci/formats/enums/FilterType.h"
#include "jace/proxy/loci/formats/enums/FontFamily.h"
#include "jace/proxy/loci/formats/enums/FontStyle.h"
#include "jace/proxy/loci/formats/enums/IEnumerationProvider.h"
#include "jace/proxy/loci/formats/enums/IlluminationType.h"
#include "jace/proxy/loci/formats/enums/Immersion.h"
#include "jace/proxy/loci/formats/enums/LaserMedium.h"
#include "jace/proxy/loci/formats/enums/LaserType.h"
#include "jace/proxy/loci/formats/enums/LineCap.h"
#include "jace/proxy/loci/formats/enums/Marker.h"
#include "jace/proxy/loci/formats/enums/Medium.h"
#include "jace/proxy/loci/formats/enums/MicrobeamManipulationType.h"
#include "jace/proxy/loci/formats/enums/MicroscopeType.h"
#include "jace/proxy/loci/formats/enums/NamingConvention.h"
#include "jace/proxy/loci/formats/enums/PixelType.h"
#include "jace/proxy/loci/formats/enums/Pulse.h"
//using namespace jace::proxy::loci::formats::enums;

#include "jace/proxy/loci/formats/enums/handler/AcquisitionModeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/ArcTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/BinningEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/ContrastMethodEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/CorrectionEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/DetectorTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/DimensionOrderEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/ExperimentTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/FilamentTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/FilterTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/FontFamilyEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/FontStyleEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/IEnumerationHandler.h"
#include "jace/proxy/loci/formats/enums/handler/IlluminationTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/ImmersionEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/LaserMediumEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/LaserTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/LineCapEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/MarkerEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/MediumEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/MicrobeamManipulationTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/MicroscopeTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/NamingConventionEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/PixelTypeEnumHandler.h"
#include "jace/proxy/loci/formats/enums/handler/PulseEnumHandler.h"
//using namespace jace::proxy::loci::formats::enums::handler;

#include "jace/proxy/loci/formats/gui/AWTImageTools.h"
#include "jace/proxy/loci/formats/gui/AWTTiffTools.h"
#include "jace/proxy/loci/formats/gui/BufferedImageReader.h"
#include "jace/proxy/loci/formats/gui/BufferedImageSource.h"
#include "jace/proxy/loci/formats/gui/BufferedImageWriter.h"
#include "jace/proxy/loci/formats/gui/CacheComponent.h"
#include "jace/proxy/loci/formats/gui/CacheIndicator.h"
#include "jace/proxy/loci/formats/gui/ComboFileFilter.h"
#include "jace/proxy/loci/formats/gui/DataConverter.h"
#include "jace/proxy/loci/formats/gui/ExtensionFileFilter.h"
#include "jace/proxy/loci/formats/gui/FormatFileFilter.h"
#include "jace/proxy/loci/formats/gui/GUITools.h"
#include "jace/proxy/loci/formats/gui/ImageViewer.h"
#include "jace/proxy/loci/formats/gui/Index16ColorModel.h"
#include "jace/proxy/loci/formats/gui/LegacyQTTools.h"
#include "jace/proxy/loci/formats/gui/NoExtensionFileFilter.h"
#include "jace/proxy/loci/formats/gui/PreviewPane.h"
#include "jace/proxy/loci/formats/gui/SignedByteBuffer.h"
#include "jace/proxy/loci/formats/gui/SignedColorModel.h"
#include "jace/proxy/loci/formats/gui/SignedShortBuffer.h"
#include "jace/proxy/loci/formats/gui/TwoChannelColorSpace.h"
#include "jace/proxy/loci/formats/gui/UnsignedIntBuffer.h"
#include "jace/proxy/loci/formats/gui/UnsignedIntColorModel.h"
#include "jace/proxy/loci/formats/gui/XMLCellRenderer.h"
#include "jace/proxy/loci/formats/gui/XMLWindow.h"
//using namespace jace::proxy::loci::formats::gui;

#include "jace/proxy/loci/formats/in/APLReader.h"
#include "jace/proxy/loci/formats/in/APNGReader.h"
#include "jace/proxy/loci/formats/in/ARFReader.h"
#include "jace/proxy/loci/formats/in/AVIReader.h"
#include "jace/proxy/loci/formats/in/AliconaReader.h"
#include "jace/proxy/loci/formats/in/AmiraReader.h"
#include "jace/proxy/loci/formats/in/AnalyzeReader.h"
#include "jace/proxy/loci/formats/in/BMPReader.h"
#include "jace/proxy/loci/formats/in/BaseTiffReader.h"
#include "jace/proxy/loci/formats/in/BioRadReader.h"
#include "jace/proxy/loci/formats/in/CellomicsReader.h"
#include "jace/proxy/loci/formats/in/DeltavisionReader.h"
#include "jace/proxy/loci/formats/in/DicomReader.h"
#include "jace/proxy/loci/formats/in/EPSReader.h"
#include "jace/proxy/loci/formats/in/FEIReader.h"
#include "jace/proxy/loci/formats/in/FV1000Reader.h"
#include "jace/proxy/loci/formats/in/FakeReader.h"
#include "jace/proxy/loci/formats/in/FitsReader.h"
#include "jace/proxy/loci/formats/in/FlexReader.h"
#include "jace/proxy/loci/formats/in/FluoviewReader.h"
#include "jace/proxy/loci/formats/in/GIFReader.h"
#include "jace/proxy/loci/formats/in/GatanReader.h"
#include "jace/proxy/loci/formats/in/GelReader.h"
#include "jace/proxy/loci/formats/in/ICSReader.h"
#include "jace/proxy/loci/formats/in/IPLabReader.h"
#include "jace/proxy/loci/formats/in/IPWReader.h"
#include "jace/proxy/loci/formats/in/ImageIOReader.h"
#include "jace/proxy/loci/formats/in/ImarisHDFReader.h"
#include "jace/proxy/loci/formats/in/ImarisReader.h"
#include "jace/proxy/loci/formats/in/ImarisTiffReader.h"
#include "jace/proxy/loci/formats/in/ImprovisionTiffReader.h"
#include "jace/proxy/loci/formats/in/InCellReader.h"
#include "jace/proxy/loci/formats/in/IvisionReader.h"
#include "jace/proxy/loci/formats/in/JPEG2000Reader.h"
#include "jace/proxy/loci/formats/in/JPEGReader.h"
#include "jace/proxy/loci/formats/in/KhorosReader.h"
#include "jace/proxy/loci/formats/in/L2DReader.h"
#include "jace/proxy/loci/formats/in/LIFReader.h"
#include "jace/proxy/loci/formats/in/LIMReader.h"
#include "jace/proxy/loci/formats/in/LegacyND2Reader.h"
#include "jace/proxy/loci/formats/in/LegacyQTReader.h"
#include "jace/proxy/loci/formats/in/LeicaHandler.h"
#include "jace/proxy/loci/formats/in/LeicaReader.h"
#include "jace/proxy/loci/formats/in/LiFlimReader.h"
#include "jace/proxy/loci/formats/in/MDBParser.h"
#include "jace/proxy/loci/formats/in/MIASReader.h"
#include "jace/proxy/loci/formats/in/MINCReader.h"
#include "jace/proxy/loci/formats/in/MNGReader.h"
#include "jace/proxy/loci/formats/in/MRCReader.h"
#include "jace/proxy/loci/formats/in/MRWReader.h"
#include "jace/proxy/loci/formats/in/MetamorphHandler.h"
#include "jace/proxy/loci/formats/in/MetamorphReader.h"
#include "jace/proxy/loci/formats/in/MetamorphTiffReader.h"
#include "jace/proxy/loci/formats/in/MicromanagerReader.h"
#include "jace/proxy/loci/formats/in/MinimalTiffReader.h"
#include "jace/proxy/loci/formats/in/NAFReader.h"
#include "jace/proxy/loci/formats/in/ND2Reader.h"
#include "jace/proxy/loci/formats/in/NRRDReader.h"
#include "jace/proxy/loci/formats/in/NativeND2Reader.h"
#include "jace/proxy/loci/formats/in/NativeQTReader.h"
#include "jace/proxy/loci/formats/in/NiftiReader.h"
#include "jace/proxy/loci/formats/in/NikonReader.h"
#include "jace/proxy/loci/formats/in/NikonTiffReader.h"
#include "jace/proxy/loci/formats/in/OMETiffReader.h"
#include "jace/proxy/loci/formats/in/OMEXMLReader.h"
#include "jace/proxy/loci/formats/in/OpenlabRawReader.h"
#include "jace/proxy/loci/formats/in/OpenlabReader.h"
#include "jace/proxy/loci/formats/in/PCIReader.h"
#include "jace/proxy/loci/formats/in/PCXReader.h"
#include "jace/proxy/loci/formats/in/PGMReader.h"
#include "jace/proxy/loci/formats/in/PSDReader.h"
#include "jace/proxy/loci/formats/in/PerkinElmerReader.h"
#include "jace/proxy/loci/formats/in/PictReader.h"
#include "jace/proxy/loci/formats/in/PrairieReader.h"
#include "jace/proxy/loci/formats/in/QTReader.h"
#include "jace/proxy/loci/formats/in/SDTInfo.h"
#include "jace/proxy/loci/formats/in/SDTReader.h"
#include "jace/proxy/loci/formats/in/SEQReader.h"
#include "jace/proxy/loci/formats/in/SVSReader.h"
#include "jace/proxy/loci/formats/in/ScanrReader.h"
#include "jace/proxy/loci/formats/in/SlidebookReader.h"
#include "jace/proxy/loci/formats/in/TCSReader.h"
#include "jace/proxy/loci/formats/in/TiffReader.h"
#include "jace/proxy/loci/formats/in/TillVisionReader.h"
#include "jace/proxy/loci/formats/in/VisitechReader.h"
#include "jace/proxy/loci/formats/in/ZeissLSMReader.h"
#include "jace/proxy/loci/formats/in/ZeissZVIReader.h"
#include "jace/proxy/loci/formats/in/ZipReader.h"
//using namespace jace::proxy::loci::formats::in;

#include "jace/proxy/loci/formats/meta/AggregateMetadata.h"
#include "jace/proxy/loci/formats/meta/DummyMetadata.h"
#include "jace/proxy/loci/formats/meta/FilterMetadata.h"
#include "jace/proxy/loci/formats/meta/IMetadata.h"
#include "jace/proxy/loci/formats/meta/IMinMaxStore.h"
#include "jace/proxy/loci/formats/meta/MetadataConverter.h"
#include "jace/proxy/loci/formats/meta/MetadataRetrieve.h"
#include "jace/proxy/loci/formats/meta/MetadataStore.h"
//using namespace jace::proxy::loci::formats::meta;

#include "jace/proxy/loci/formats/ome/OMEXML2003FCMetadata.h"
#include "jace/proxy/loci/formats/ome/OMEXML200706Metadata.h"
#include "jace/proxy/loci/formats/ome/OMEXML200802Metadata.h"
#include "jace/proxy/loci/formats/ome/OMEXML200809Metadata.h"
#include "jace/proxy/loci/formats/ome/OMEXMLMetadata.h"
#include "jace/proxy/loci/formats/ome/OmeisException.h"
#include "jace/proxy/loci/formats/ome/OmeisImporter.h"
//using namespace jace::proxy::loci::formats::ome;

#include "jace/proxy/loci/formats/out/APNGWriter.h"
#include "jace/proxy/loci/formats/out/AVIWriter.h"
#include "jace/proxy/loci/formats/out/EPSWriter.h"
#include "jace/proxy/loci/formats/out/ICSWriter.h"
#include "jace/proxy/loci/formats/out/ImageIOWriter.h"
#include "jace/proxy/loci/formats/out/JPEG2000Writer.h"
#include "jace/proxy/loci/formats/out/JPEGWriter.h"
#include "jace/proxy/loci/formats/out/LegacyQTWriter.h"
#include "jace/proxy/loci/formats/out/OMETiffWriter.h"
#include "jace/proxy/loci/formats/out/OMEXMLWriter.h"
#include "jace/proxy/loci/formats/out/QTWriter.h"
#include "jace/proxy/loci/formats/out/TiffWriter.h"
//using namespace jace::proxy::loci::formats::out;

#include "jace/proxy/loci/formats/tiff/IFD.h"
#include "jace/proxy/loci/formats/tiff/IFDList.h"
#include "jace/proxy/loci/formats/tiff/PhotoInterp.h"
#include "jace/proxy/loci/formats/tiff/TiffCompression.h"
#include "jace/proxy/loci/formats/tiff/TiffConstants.h"
#include "jace/proxy/loci/formats/tiff/TiffIFDEntry.h"
#include "jace/proxy/loci/formats/tiff/TiffParser.h"
#include "jace/proxy/loci/formats/tiff/TiffRational.h"
#include "jace/proxy/loci/formats/tiff/TiffSaver.h"
#include "jace/proxy/loci/formats/tiff/TiffTools.h"
//using namespace jace::proxy::loci::formats::tiff;

#include "jace/proxy/loci/formats/tools/AmiraParameters.h"
#include "jace/proxy/loci/formats/tools/CacheConsole.h"
#include "jace/proxy/loci/formats/tools/EditTiffG.h"
#include "jace/proxy/loci/formats/tools/ImageConverter.h"
#include "jace/proxy/loci/formats/tools/ImageInfo.h"
#include "jace/proxy/loci/formats/tools/PrintDomains.h"
#include "jace/proxy/loci/formats/tools/PrintFormatTable.h"
#include "jace/proxy/loci/formats/tools/StatusEchoer.h"
#include "jace/proxy/loci/formats/tools/TiffComment.h"
#include "jace/proxy/loci/formats/tools/XMLIndent.h"
#include "jace/proxy/loci/formats/tools/XMLValidate.h"
//using namespace jace::proxy::loci::formats::tools;

#endif
