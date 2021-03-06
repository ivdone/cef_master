// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CEF_LIBCEF_BROWSER_PRINTING_PRINT_VIEW_MANAGER_H_
#define CEF_LIBCEF_BROWSER_PRINTING_PRINT_VIEW_MANAGER_H_

#include "include/internal/cef_types_wrappers.h"

#include "base/macros.h"
#include "content/public/browser/web_contents_user_data.h"

class CefBrowserInfo;

namespace content {
class RenderFrameHost;
class RenderProcessHost;
class WebContentsObserver;
}  // namespace content

struct PrintHostMsg_DidPreviewDocument_Params;
struct PrintHostMsg_RequestPrintPreview_Params;

namespace printing {

// Manages the print commands for a WebContents.
class CefPrintViewManager
    : public content::WebContentsObserver,
      public content::WebContentsUserData<CefPrintViewManager> {
 public:
  ~CefPrintViewManager() override;

  // Callback executed on PDF printing completion.
  typedef base::Callback<void(bool /*ok*/)> PdfPrintCallback;

  // Print the current document to a PDF file. Execute |callback| on completion.
  bool PrintToPDF(content::RenderFrameHost* rfh,
                  const base::FilePath& path,
                  const CefPdfPrintSettings& settings,
                  const PdfPrintCallback& callback);
  // Call to Chrome's PrintViewManager
  bool PrintPreviewNow(content::RenderFrameHost* rfh, bool has_selection);

  // content::WebContentsObserver implementation.
  void RenderFrameDeleted(content::RenderFrameHost* render_frame_host) override;
  void NavigationStopped() override;
  void RenderProcessGone(base::TerminationStatus status) override;
  bool OnMessageReceived(const IPC::Message& message,
                         content::RenderFrameHost* render_frame_host) override;

  class CefPrintPreviewHelper
      : public content::WebContentsObserver,
        public content::WebContentsUserData<CefPrintPreviewHelper> {
   public:
    void InitializeForCef();
    void WebContentsDestroyed() override;

   private:
    scoped_refptr<CefBrowserInfo> browser_info_;
    explicit CefPrintPreviewHelper(content::WebContents* contents);
    friend class content::WebContentsUserData<CefPrintPreviewHelper>;
    DISALLOW_COPY_AND_ASSIGN(CefPrintPreviewHelper);
  };

 private:
  explicit CefPrintViewManager(content::WebContents* web_contents);
  friend class content::WebContentsUserData<CefPrintViewManager>;

  // IPC Message handlers.
  void OnRequestPrintPreview(const PrintHostMsg_RequestPrintPreview_Params&);
  void OnShowScriptedPrintPreview(content::RenderFrameHost* rfh,
                                  bool source_is_modifiable);
  void OnRequestPrintPreview_PrintToPdf(
      const PrintHostMsg_RequestPrintPreview_Params&);
  void OnDidShowPrintDialog_PrintToPdf(content::RenderFrameHost* rfh);
  void OnMetafileReadyForPrinting_PrintToPdf(
      const PrintHostMsg_DidPreviewDocument_Params&);
  void InitializePrintPreviewForCef();
  void TerminatePdfPrintJob();

  // Used for printing to PDF. Only accessed on the browser process UI thread.
  int next_pdf_request_id_ = -1;
  struct PdfPrintState;
  std::unique_ptr<PdfPrintState> pdf_print_state_;

  DISALLOW_COPY_AND_ASSIGN(CefPrintViewManager);
};

}  // namespace printing

#endif  // CEF_LIBCEF_BROWSER_PRINTING_PRINT_VIEW_MANAGER_H_