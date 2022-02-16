#include "opentelemetry/exporters/ostream/span_exporter.h"
#include "opentelemetry/exporters/ostream/span_exporter_wrapper.h"

using namespace opentelemetry::exporter::trace;

extern "C" {
        COStreamSpanExporter *newOStreamSpanExporter() {
          OStreamSpanExporter* abc = new OStreamSpanExporter;
                return reinterpret_cast<COStreamSpanExporter*>(abc);
        }
       void deleteOStreamSpanExporter(COStreamSpanExporter *v) {
          OStreamSpanExporter* abc = reinterpret_cast<OStreamSpanExporter *>(v);
                delete abc;
        }
}
