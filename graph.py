import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("output/rc_estimate_results.csv")
df.columns = df.columns.str.strip()
df = df.sort_values("n")

n = df["n"]
r = df["r"]

# Smoothed line (moving average)
window_size = 5
r_smooth = r.rolling(window=window_size, center=True).mean()

# Plot
plt.figure(figsize=(10, 6))
plt.plot(n, r, marker='o', label="Estimated $r_c$")
plt.plot(n, r_smooth, linewidth=2, label="Smoothed $r_c$")

plt.xlabel("n")
plt.ylabel("$r_c$ estimate")
plt.title("$r_c$ Estimate vs n")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig("output/rc_plot.png", dpi=300)

plt.close()