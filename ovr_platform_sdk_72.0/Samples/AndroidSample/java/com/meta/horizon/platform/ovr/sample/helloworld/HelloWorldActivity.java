package com.meta.horizon.platform.ovr.sample.helloworld;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import com.meta.horizon.platform.ovr.Core;
import com.meta.horizon.platform.ovr.Error;
import com.meta.horizon.platform.ovr.enums.PlatformInitializeResult;
import com.meta.horizon.platform.ovr.models.AchievementDefinitionArray;
import com.meta.horizon.platform.ovr.models.ApplicationVersion;
import com.meta.horizon.platform.ovr.models.LeaderboardArray;
import com.meta.horizon.platform.ovr.models.PlatformInitialize;
import com.meta.horizon.platform.ovr.models.Product;
import com.meta.horizon.platform.ovr.models.ProductArray;
import com.meta.horizon.platform.ovr.models.Purchase;
import com.meta.horizon.platform.ovr.models.PurchaseArray;
import com.meta.horizon.platform.ovr.models.User;
import com.meta.horizon.platform.ovr.requests.Achievements;
import com.meta.horizon.platform.ovr.requests.Application;
import com.meta.horizon.platform.ovr.requests.Entitlements;
import com.meta.horizon.platform.ovr.requests.IAP;
import com.meta.horizon.platform.ovr.requests.Leaderboards;
import com.meta.horizon.platform.ovr.requests.Request;
import com.meta.horizon.platform.ovr.requests.Users;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class HelloWorldActivity extends Activity {

  ExecutorService executorService = Executors.newFixedThreadPool(1);

  private static final String TAG = "HelloWorld";

  private static final String APP_ID = "8101217906588347";

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    TextView text = new TextView(this);
    text.setHint("Hello World!");
    setContentView(text);

    executorService.execute(
        new Runnable() {
          @Override
          public void run() {
            if (!Core.isInitialized()) {
              initializePSDK();
            } else {
              // already initialized, so just run
              postInitialize();
            }
          }
        });
  }

  private void initializePSDK() {
    Log.i(TAG, "Initializing PSDK Core...");
    Request<PlatformInitialize> req = Core.asyncInitialize(APP_ID, HelloWorldActivity.this);
    req.onSuccess(
            result -> {
              if (result.getResult() == PlatformInitializeResult.Success) {
                Log.i(TAG, "Initialized PSDK Core!");
                postInitialize();
              } else {
                // failed!
                Log.i(TAG, "Failed to initialize PSDK Core!");
              }
            })
        .onError((Request.Handler<Error>) error -> Log.e(TAG, error.getMessage()));
  }

  private void postInitialize() {
    Request entitled = Entitlements.getIsViewerEntitled();
    Log.i(TAG, "Entitlements.getIsViewerEntitled() request id: " + entitled.getRequestId());
    entitled
        .onSuccess(n -> Log.i(TAG, "User is entitled to app"))
        .onError((Request.Handler<Error>) error -> Log.e(TAG, error.getMessage()));

    long userId = Core.getLoggedInUserID();
    Log.i(TAG, "Logged in user id: " + userId);

    Request<User> userReq = Users.getLoggedInUser();
    Log.i(TAG, "User.getLoggedInUser() request id: " + userReq.getRequestId());
    userReq
        .onSuccess(
            user ->
                Log.i(
                    TAG,
                    "User: "
                        + user.getDisplayName()
                        + ", id: "
                        + user.getID()
                        + ", imageURL: "
                        + user.getImageURL()))
        .onError(
            (Request.Handler<Error>)
                error -> Log.e(TAG, "Failed to get logged in user: " + error.getMessage()));

    Request<AchievementDefinitionArray> achievements = Achievements.getAllDefinitions();
    Log.i(TAG, "Achievements.getAllDefinitions() request id: " + achievements.getRequestId());
    achievements
        .onSuccess(array -> Log.i(TAG, "Achievements: " + array.getElements()))
        .onError(
            (Request.Handler<Error>)
                error ->
                    Log.e(TAG, "Failed to get achievement definitions: " + error.getMessage()));

    Request<ApplicationVersion> versionReq = Application.getVersion();
    Log.i(TAG, "Application.getVersion() request id: " + versionReq.getRequestId());
    versionReq
        .onSuccess(
            v ->
                Log.i(
                    TAG,
                    "Version: "
                        + v.getLatestCode()
                        + ", size: "
                        + v.getSize()
                        + ", name: "
                        + v.getLatestName()))
        .onError(
            (Request.Handler<Error>)
                error -> Log.e(TAG, "Failed to get application version: " + error.getMessage()));

    Request<LeaderboardArray> req = Leaderboards.get("leaderboard1");
    Log.i(TAG, "Leaderboards request id: " + req.getRequestId());
    req.onSuccess(
            leaderboardArray -> Log.i(TAG, "Leaderboard is: " + leaderboardArray.getElements()))
        .onError(
            (Request.Handler<Error>)
                error -> Log.e(TAG, "Failed to get leaderboard: " + error.getMessage()));

    final String freeDurableSKU = "sku_free_durable_1";
    Request<PurchaseArray> purchases = IAP.getViewerPurchases();
    purchases
        .onSuccess(
            purchaseArray -> {
              Log.i(TAG, "Users purchases are: ");
              List<Purchase> list = purchaseArray.getElements();
              boolean containsFreeDurable = false;
              if (!list.isEmpty()) {
                List<String> skus = new ArrayList<>(list.size());
                for (Purchase purchase : list) {
                  final String sku = purchase.getSku();
                  Log.i(TAG, "- SKU: " + sku);
                  Log.i(TAG, "- Grant Time: " + purchase.getGrantTime());
                  skus.add(sku);
                  if (freeDurableSKU.equals(sku)) {
                    containsFreeDurable = true;
                  }
                }

                Request<ProductArray> iapGetProducts =
                    IAP.getProductsBySKU(skus.toArray(new String[0]));
                Log.i(TAG, "IAP.getProductsBySKU() request id: " + iapGetProducts.getRequestId());
                iapGetProducts
                    .onSuccess(
                        products -> {
                          Log.i(TAG, "Products are: " + products.getElements());
                          List<Product> productList = products.getElements();
                          if (!productList.isEmpty()) {
                            for (Product product : productList) {
                              Log.i(
                                  TAG,
                                  "- SKU: " + product.getSku() + ", name: " + product.getName());
                            }
                          }
                        })
                    .onError(
                        (Request.Handler<Error>)
                            error ->
                                Log.e(TAG, "Failed to get products by SKU: " + error.getMessage()));
              }
              if (!containsFreeDurable) {
                Request<Purchase> purchase = IAP.launchCheckoutFlow("gas");
                Log.i(TAG, "IAP.launchCheckoutFlow() request id: " + purchase.getRequestId());
                purchase
                    .onSuccess(
                        p -> {
                          Log.i(TAG, "purchase id: " + p.getID());
                        })
                    .onError(
                        (Request.Handler<Error>)
                            error -> {
                              int code = error.getCode();
                              int httpCode = error.getHttpCode();
                              String message = error.getMessage();
                              String displayable = error.getDisplayableMessage();
                              Log.e(TAG, "Failed to get checkout by SKU: " + message);
                            });
              }
            })
        .onError(
            (Request.Handler<Error>)
                error -> Log.e(TAG, "Failed to get viewer purchases: " + error.getMessage()));
  }
}
